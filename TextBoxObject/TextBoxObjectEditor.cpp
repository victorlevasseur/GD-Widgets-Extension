/**

Game Develop - Text Object Extension
Copyright (c) 2008-2013 Florian Rival (Florian.Rival@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.

*/

#if defined(GD_IDE_ONLY)

#include "TextBoxObjectEditor.h"

//(*InternalHeaders(TextBoxObjectEditor)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/colordlg.h>
#include <wx/filename.h>
#include <wx/filedlg.h>

#include <iostream>
#include <vector>

#include "GDCore/PlatformDefinition/Project.h"
#include "GDCore/IDE/Dialogs/MainFrameWrapper.h"
#include "GDCore/CommonTools.h"
#include "TextBoxObject.h"

#include "WidgetsCore/PaletteEditor.h"

//(*IdInit(TextBoxObjectEditor)
const long TextBoxObjectEditor::ID_TEXTCTRL1 = wxNewId();
const long TextBoxObjectEditor::ID_CHECKBOX2 = wxNewId();
const long TextBoxObjectEditor::ID_CHECKBOX1 = wxNewId();
const long TextBoxObjectEditor::ID_TEXTCTRL3 = wxNewId();
const long TextBoxObjectEditor::ID_STATICTEXT3 = wxNewId();
const long TextBoxObjectEditor::ID_TEXTCTRL4 = wxNewId();
const long TextBoxObjectEditor::ID_BUTTON3 = wxNewId();
const long TextBoxObjectEditor::ID_STATICTEXT1 = wxNewId();
const long TextBoxObjectEditor::ID_SPINCTRL2 = wxNewId();
const long TextBoxObjectEditor::ID_STATICTEXT2 = wxNewId();
const long TextBoxObjectEditor::ID_TEXTCTRL2 = wxNewId();
const long TextBoxObjectEditor::ID_BUTTON4 = wxNewId();
const long TextBoxObjectEditor::ID_STATICTEXT4 = wxNewId();
const long TextBoxObjectEditor::ID_SPINCTRL1 = wxNewId();
const long TextBoxObjectEditor::ID_STATICLINE1 = wxNewId();
const long TextBoxObjectEditor::ID_BUTTON1 = wxNewId();
const long TextBoxObjectEditor::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TextBoxObjectEditor,wxDialog)
	//(*EventTable(TextBoxObjectEditor)
	//*)
END_EVENT_TABLE()

TextBoxObjectEditor::TextBoxObjectEditor( wxWindow* parent, gd::Project & game_, TextBoxObject & object_, gd::MainFrameWrapper & mainFrameWrapper_) :
game(game_),
object(object_),
mainFrameWrapper(mainFrameWrapper_)
{
	//(*Initialize(TextBoxObjectEditor)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Edit the TextBox object"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Text"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	textTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(279,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer6->Add(textTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	canSelectCheckBox = new wxCheckBox(this, ID_CHECKBOX2, _("Allow text selection"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	canSelectCheckBox->SetValue(false);
	FlexGridSizer6->Add(canSelectCheckBox, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer7->AddGrowableCol(1);
	hideCharCheckBox = new wxCheckBox(this, ID_CHECKBOX1, _("Hide character :"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	hideCharCheckBox->SetValue(false);
	hideCharCheckBox->SetToolTip(_("The hide character is a character that hide real\ncharacters to be shown in the text box\n(for a password for example)."));
	FlexGridSizer7->Add(hideCharCheckBox, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	hideCharTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	hideCharTextCtrl->SetMaxLength(1);
	hideCharTextCtrl->Disable();
	hideCharTextCtrl->SetToolTip(_("The hide character is a character that hide real\ncharacters to be shown in the text box\n(for a password for example)."));
	FlexGridSizer7->Add(hideCharTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Placeholder :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	placeholderTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	placeholderTextCtrl->SetToolTip(_("The placeholder is a text shown when the text box\nis empty and doesn\'t have the focus to give an indication."));
	FlexGridSizer7->Add(placeholderTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer1->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Others properties"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3->AddGrowableCol(1);
	FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	colorBt = new wxButton(this, ID_BUTTON3, _("Edit the color palette"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer3->Add(colorBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Border thickness :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	borderSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL2"));
	borderSpinCtrl->SetValue(_T("0"));
	FlexGridSizer3->Add(borderSpinCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Font :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer4->AddGrowableCol(0);
	fontEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(75,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer4->Add(fontEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	fontBt = new wxButton(this, ID_BUTTON4, _("Choose the font"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer4->Add(fontBt, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Size :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer5->AddGrowableCol(0);
	sizeEdit = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0, _T("ID_SPINCTRL1"));
	sizeEdit->SetValue(_T("0"));
	FlexGridSizer5->Add(sizeEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	okBt = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(okBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelBt = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(cancelBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&TextBoxObjectEditor::OnhideCharCheckBoxClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TextBoxObjectEditor::OncolorBtClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TextBoxObjectEditor::OnfontBtClick);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&TextBoxObjectEditor::OnSizeEditChange);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TextBoxObjectEditor::OnokBtClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TextBoxObjectEditor::OncancelBtClick);
	//*)

    textTextCtrl->SetValue(object.GetString().toAnsiString().c_str());
    canSelectCheckBox->SetValue(object.IsAllowingTextSelection());

    sf::Uint32 hideChar = object.GetHideCharacter();
    sf::String hideCharStr(hideChar);
    hideCharCheckBox->SetValue(hideChar != sf::Uint32(0));
    hideCharTextCtrl->Enable(hideChar != sf::Uint32(0));
    if(hideChar != sf::Uint32(0))
        hideCharTextCtrl->SetValue(hideCharStr.toAnsiString().c_str());

    placeholderTextCtrl->SetValue(object.GetPlaceholder().toAnsiString().c_str());

    borderSpinCtrl->SetValue(object.GetBorderThickness());
    fontEdit->SetValue(object.GetFontFilename().c_str());
    sizeEdit->SetValue(object.GetCharacterSize());

    m_palette = WCore::Palette(object.GetWidgetPalette());
}

TextBoxObjectEditor::~TextBoxObjectEditor()
{
	//(*Destroy(TextBoxObjectEditor)
	//*)
}

void TextBoxObjectEditor::OnokBtClick(wxCommandEvent& event)
{
    object.SetString(gd::ToString(textTextCtrl->GetValue()));
    object.AllowTextSelection(canSelectCheckBox->GetValue());

    if(hideCharCheckBox->GetValue())
    {
        sf::String hideCharStr(gd::ToString(hideCharTextCtrl->GetValue()));
        object.SetHideCharacter(hideCharStr[0]);
    }
    else
    {
        object.SetHideCharacter(sf::Uint32(0));
    }

    object.SetPlaceholder(gd::ToString(placeholderTextCtrl->GetValue()));


    object.SetBorderThickness(borderSpinCtrl->GetValue());
    object.SetFontFilename(gd::ToString(fontEdit->GetValue()));
    object.SetCharacterSize(sizeEdit->GetValue());

    object.SetWidgetPalette(m_palette);

    EndModal(1);
}

void TextBoxObjectEditor::OncancelBtClick(wxCommandEvent& event)
{
    EndModal(0);
}

void TextBoxObjectEditor::OncolorBtClick(wxCommandEvent& event)
{
    std::vector<WCore::ColorMetadata> colorsToEdit;
    colorsToEdit.push_back(WCore::ColorMetadata("text", _("Text"), WCore::ColorMetadata::ALL_STATES_COLOR));
    colorsToEdit.push_back(WCore::ColorMetadata("placeholder", _("Placeholder"), WCore::ColorMetadata::ALL_STATES_COLOR));
    colorsToEdit.push_back(WCore::ColorMetadata("background", _("Background"), WCore::ColorMetadata::ALL_STATES_COLOR));
    colorsToEdit.push_back(WCore::ColorMetadata("border", _("Border"), WCore::ColorMetadata::ALL_STATES_COLOR));
    colorsToEdit.push_back(WCore::ColorMetadata("selection", _("Selection"), WCore::ColorMetadata::ALL_STATES_COLOR));

    WCore::PaletteEditor editor(this, m_palette, colorsToEdit);

    if(editor.ShowModal() == 1)
    {
        m_palette = editor.GetPalette();
    }
}

void TextBoxObjectEditor::OnfontBtClick(wxCommandEvent& event)
{
    wxString gameDirectory = wxFileName::FileName(game.GetProjectFile()).GetPath();
    wxFileDialog fileDialog(this, _("Choose a font ( ttf/ttc files )"), gameDirectory, "", "Polices (*.ttf, *.ttc)|*.ttf;*.ttc");

    if ( fileDialog.ShowModal() == wxID_OK )
    {
        //Note that the file is relative to the project directory
        wxFileName filename(fileDialog.GetPath()); filename.MakeRelativeTo(gameDirectory);
        fontEdit->SetValue(filename.GetFullPath());
    }
}

void TextBoxObjectEditor::OnSizeEditChange(wxSpinEvent& event)
{

}

void TextBoxObjectEditor::OnhideCharCheckBoxClick(wxCommandEvent& event)
{
    hideCharTextCtrl->Enable(hideCharCheckBox->GetValue());
}
#endif
