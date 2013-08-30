#include "WidgetsCore/PaletteEditor.h"

#if defined(GD_IDE_ONLY)

#include <iostream>

#include <SFML/Graphics/Color.hpp>

#include "GDCore/CommonTools.h"

#include <wx/propgrid/property.h>
#include <wx/propgrid/advprops.h>

#include "WidgetsCore/ColorTools.h"

//(*InternalHeaders(PaletteEditor)
#include <wx/intl.h>
#include <wx/string.h>
//*)

namespace WCore
{

//(*IdInit(PaletteEditor)
const long PaletteEditor::ID_PANEL1 = wxNewId();
const long PaletteEditor::ID_BUTTON1 = wxNewId();
const long PaletteEditor::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PaletteEditor,wxDialog)
	//(*EventTable(PaletteEditor)
	//*)
END_EVENT_TABLE()

PaletteEditor::PaletteEditor(wxWindow* parent, Palette palette, std::vector<std::pair<std::string, wxString> > colorsToEdit, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
	//(*Initialize(PaletteEditor)
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Edit the palette"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	propgridPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	propgridSizer = new wxFlexGridSizer(0, 3, 0, 0);
	propgridSizer->AddGrowableCol(0);
	propgridSizer->AddGrowableRow(0);
	propgridPanel->SetSizer(propgridSizer);
	propgridSizer->Fit(propgridPanel);
	propgridSizer->SetSizeHints(propgridPanel);
	FlexGridSizer2->Add(propgridPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	okBt = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(okBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelBt = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(cancelBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PaletteEditor::OnokBtClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PaletteEditor::OncancelBtClick);
	//*)

	m_palette = palette;
	//m_palette.SetColor("text", SFW::ENABLED|SFW::HOVERED|SFW::FOCUSED, sf::Color(255, 0, 0));

	//Creating the propertyTree
	long GRIDID = wxNewId();

    m_propgrid = new wxPropertyGrid(propgridPanel, // parent
                                    GRIDID, // id
                                    wxDefaultPosition, // position
                                    wxSize(300,340), // size
                                    wxPG_SPLITTER_AUTO_CENTER |
                                    wxPG_DEFAULT_STYLE );

    m_propgrid->SetExtraStyle( wxPG_EX_HELP_AS_TOOLTIPS );
    propgridSizer->Add(m_propgrid, 1, wxALL|wxEXPAND, 0);

	//Creating the properties
	for(unsigned int a = 0; a < colorsToEdit.size(); a++)
    {
        m_colorsList.push_back(colorsToEdit[a].first);

        std::string &colorName = colorsToEdit[a].first;

        m_propgrid->Append(new wxPropertyCategory(colorsToEdit[a].second, colorName));
        {
            m_propgrid->AppendIn(wxString(colorName.c_str()), new wxColourProperty(_("Disabled"), "disabled", ToWxColour(m_palette.GetColor(colorName, DISABLED))));
            m_propgrid->AppendIn(wxString(colorName.c_str()), new wxColourProperty(_("Enabled"), "enabled", ToWxColour(m_palette.GetColor(colorName, ENABLED))));
            m_propgrid->AppendIn(wxString(colorName.c_str()), new wxColourProperty(_("Hovered"), "hovered", ToWxColour(m_palette.GetColor(colorName, HOVERED))));
            m_propgrid->AppendIn(wxString(colorName.c_str()), new wxColourProperty(_("Focused"), "focused", ToWxColour(m_palette.GetColor(colorName, FOCUSED))));
            m_propgrid->AppendIn(wxString(colorName.c_str()), new wxColourProperty(_("Focused and hovered"), "focusedhovered", ToWxColour(m_palette.GetColor(colorName, FOCUSED_HOVERED))));
        }
    }

    m_propgrid->SetPropertyAttributeAll("HasAlpha", true);

    SetSize(300, 600);
}

PaletteEditor::~PaletteEditor()
{
	//(*Destroy(PaletteEditor)
	//*)
}

Palette PaletteEditor::GetPalette() const
{
    return m_palette;
}

void PaletteEditor::OnokBtClick(wxCommandEvent& event)
{
    for(int a = 0; a < m_colorsList.size(); a++)
    {
        m_palette.SetColor(m_colorsList.at(a), DISABLED,
                           ToSfColor(m_propgrid->GetPropertyValue(wxString(m_colorsList.at(a).c_str()) + wxString(".disabled"))));

        m_palette.SetColor(m_colorsList.at(a), ENABLED,
                           ToSfColor(m_propgrid->GetPropertyValue(wxString(m_colorsList.at(a).c_str()) + wxString(".enabled"))));

        m_palette.SetColor(m_colorsList.at(a), HOVERED,
                           ToSfColor(m_propgrid->GetPropertyValue(wxString(m_colorsList.at(a).c_str()) + wxString(".hovered"))));

        m_palette.SetColor(m_colorsList.at(a), FOCUSED,
                           ToSfColor(m_propgrid->GetPropertyValue(wxString(m_colorsList.at(a).c_str()) + wxString(".focused"))));

        m_palette.SetColor(m_colorsList.at(a), FOCUSED_HOVERED,
                           ToSfColor(m_propgrid->GetPropertyValue(wxString(m_colorsList.at(a).c_str()) + wxString(".focusedhovered"))));

    }

    EndModal(1);
}

void PaletteEditor::OncancelBtClick(wxCommandEvent& event)
{
    EndModal(0);
}

}

#endif
