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

#ifndef TextBoxObjectEDITOR_H
#define TextBoxObjectEDITOR_H

//(*Headers(TextBoxObjectEditor)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include "WidgetsCore/Palette.h"

namespace gd { class Project; }
class TextBoxObject;
namespace gd { class MainFrameWrapper; }

class TextBoxObjectEditor: public wxDialog
{
	public:

		TextBoxObjectEditor( wxWindow* parent, gd::Project & game_, TextBoxObject & object_, gd::MainFrameWrapper & mainFrameWrapper_);
		virtual ~TextBoxObjectEditor();

		//(*Declarations(TextBoxObjectEditor)
		wxSpinCtrl* sizeEdit;
		wxTextCtrl* hideCharTextCtrl;
		wxStaticText* StaticText2;
		wxCheckBox* canSelectCheckBox;
		wxTextCtrl* textTextCtrl;
		wxStaticText* StaticText1;
		wxButton* cancelBt;
		wxButton* fontBt;
		wxButton* colorBt;
		wxSpinCtrl* borderSpinCtrl;
		wxStaticLine* StaticLine1;
		wxTextCtrl* fontEdit;
		wxStaticText* StaticText4;
		wxButton* okBt;
		wxCheckBox* hideCharCheckBox;
		//*)

	protected:

		//(*Identifiers(TextBoxObjectEditor)
		static const long ID_TEXTCTRL1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX1;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL1;
		static const long ID_STATICLINE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(TextBoxObjectEditor)
		void OnokBtClick(wxCommandEvent& event);
		void OncolorBtClick(wxCommandEvent& event);
		void OnfontBtClick(wxCommandEvent& event);
		void OnSizeEditChange(wxSpinEvent& event);
		void OncancelBtClick(wxCommandEvent& event);
		//*)

		gd::Project & game;
		TextBoxObject & object;
		gd::MainFrameWrapper & mainFrameWrapper;

		WCore::Palette m_palette;

		DECLARE_EVENT_TABLE()
};

#endif
#endif

