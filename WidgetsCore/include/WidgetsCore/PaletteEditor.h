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
        COLOR_FOR_DISABLED = 1,
        COLOR_FOR_ENABLED = 2,
        COLOR_FOR_HOVERED = 4,
        COLOR_FOR_FOCUSED = 8,
        COLOR_FOR_FOCUSEDHOVERED = 16,

        UNIQUE_COLOR_FOR_ALL = 32,

        COLOR_FOR_EACH = COLOR_FOR_DISABLED|COLOR_FOR_ENABLED|COLOR_FOR_HOVERED|COLOR_FOR_FOCUSED|COLOR_FOR_FOCUSEDHOVERED,
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
