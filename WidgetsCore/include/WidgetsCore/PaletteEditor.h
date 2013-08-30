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

class WIDGETS_CORE_API PaletteEditor: public wxDialog
{
	public:

		PaletteEditor(wxWindow* parent, Palette palette, std::vector<std::pair<std::string, wxString> > colorsToEdit, wxWindowID id=wxID_ANY, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize);
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
		std::vector<std::string> m_colorsList;

		wxPropertyGrid *m_propgrid;
};

}

#endif

#endif
