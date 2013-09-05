#ifndef PALETTEEDITOR_H
#define PALETTEEDITOR_H

#if defined(GD_IDE_ONLY)

#include <vector>

#include "WidgetsCore/Defs.h"
#include "WidgetsCore/Palette.h"

//(*Headers(PaletteEditor)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
#include <wx/propgrid/propgrid.h>

namespace WCore
{

struct WIDGETS_CORE_API ColorMetadata
{
    typedef int EditableStateColors;

    enum EditableStateColor
    {
        DISABLED_COLOR = 1,
        ENABLED_COLOR = 2,
        HOVERED_COLOR = 4,
        FOCUSED_COLOR = 8,
        FOCUSED_HOVERED_COLOR = 16,

        UNIQUE_COLOR = 32,

        ALL_STATES_COLOR = DISABLED_COLOR|ENABLED_COLOR|HOVERED_COLOR|FOCUSED_COLOR|FOCUSED_HOVERED_COLOR,
    };

    ColorMetadata(const std::string &colorId_, wxString colorName_, EditableStateColors editableStateColors_)
    {
        colorId = colorId_;
        colorName = colorName_;
        editableStateColors = editableStateColors_;
    }

    std::string colorId;
    wxString colorName;
    EditableStateColors editableStateColors;
};

class WIDGETS_CORE_API PaletteEditor: public wxDialog
{
	public:

		PaletteEditor(wxWindow* parent, Palette palette, std::vector< ColorMetadata > colorsToEdit, wxWindowID id=wxID_ANY, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize);
		virtual ~PaletteEditor();

		Palette GetPalette() const;

		//(*Declarations(PaletteEditor)
		wxPanel* propgridPanel;
		wxButton* cancelBt;
		wxFlexGridSizer* propgridSizer;
		wxButton* okBt;
		//*)

	protected:

		//(*Identifiers(PaletteEditor)
		static const long ID_PANEL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(PaletteEditor)
		void OnokBtClick(wxCommandEvent& event);
		void OncancelBtClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		Palette m_palette;
		std::vector<ColorMetadata> m_colorsList;

		wxPropertyGrid *m_propgrid;
};

}

#endif

#endif
