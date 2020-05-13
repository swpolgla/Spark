///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 May  9 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/gbsizer.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Spark
///////////////////////////////////////////////////////////////////////////////
class Spark : public wxFrame
{
	private:

	protected:
		wxRichTextCtrl* math_input;
		wxRichTextCtrl* math_output;
		wxMenuBar* menubar;
		wxMenu* file_menu_tab;
		wxMenu* edit_menu_tab;
		wxMenu* help_menu_tab;

		// Virtual event handlers, overide them in your derived class
		virtual void math_input_evt( wxCommandEvent& event ) { event.Skip(); }


	public:

		Spark( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Spark"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Spark();

};

