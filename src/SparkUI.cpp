///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 May  9 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SparkUI.h"

///////////////////////////////////////////////////////////////////////////

Spark::Spark( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 0, 0 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	math_input = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxWANTS_CHARS );
	math_input->SetFont( wxFont( 16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("PT Mono") ) );

	gbSizer2->Add( math_input, wxGBPosition( 0, 0 ), wxGBSpan( 1, 3 ), wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );

	math_output = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxWANTS_CHARS );
	math_output->SetFont( wxFont( 16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("PT Mono") ) );

	gbSizer2->Add( math_output, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxBOTTOM|wxEXPAND|wxTOP, 5 );

	math_scrollbar = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL );
	gbSizer2->Add( math_scrollbar, wxGBPosition( 0, 4 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );


	gbSizer2->AddGrowableCol( 0 );
	gbSizer2->AddGrowableCol( 1 );
	gbSizer2->AddGrowableCol( 2 );
	gbSizer2->AddGrowableCol( 3 );
	gbSizer2->AddGrowableRow( 0 );

	this->SetSizer( gbSizer2 );
	this->Layout();
	menubar = new wxMenuBar( 0 );
	file_menu_tab = new wxMenu();
	wxMenuItem* file_menu_exit;
	file_menu_exit = new wxMenuItem( file_menu_tab, wxID_EXIT, wxString( wxT("E&xit\tAlt+X") ) , wxT("Quit this program"), wxITEM_NORMAL );
	file_menu_tab->Append( file_menu_exit );

	menubar->Append( file_menu_tab, wxT("File") );

	edit_menu_tab = new wxMenu();
	wxMenuItem* edit_menu_undo;
	edit_menu_undo = new wxMenuItem( edit_menu_tab, wxID_UNDO, wxString( wxT("&Undo\tCtrl+Z") ) , wxEmptyString, wxITEM_NORMAL );
	edit_menu_tab->Append( edit_menu_undo );

	wxMenuItem* edit_menu_redo;
	edit_menu_redo = new wxMenuItem( edit_menu_tab, wxID_REDO, wxString( wxT("&Redo\tCtrl+Shift+Z") ) , wxEmptyString, wxITEM_NORMAL );
	edit_menu_tab->Append( edit_menu_redo );

	edit_menu_tab->AppendSeparator();

	wxMenuItem* edit_menu_cut;
	edit_menu_cut = new wxMenuItem( edit_menu_tab, wxID_CUT, wxString( wxT("&Cut\tCtrl+X") ) , wxEmptyString, wxITEM_NORMAL );
	edit_menu_tab->Append( edit_menu_cut );

	wxMenuItem* edit_menu_copy;
	edit_menu_copy = new wxMenuItem( edit_menu_tab, wxID_COPY, wxString( wxT("&Copy\tCtrl+C") ) , wxEmptyString, wxITEM_NORMAL );
	edit_menu_tab->Append( edit_menu_copy );

	wxMenuItem* edit_menu_paste;
	edit_menu_paste = new wxMenuItem( edit_menu_tab, wxID_PASTE, wxString( wxT("&Paste\tCtrl+V") ) , wxEmptyString, wxITEM_NORMAL );
	edit_menu_tab->Append( edit_menu_paste );

	edit_menu_tab->AppendSeparator();

	wxMenuItem* edit_menu_select_all;
	edit_menu_select_all = new wxMenuItem( edit_menu_tab, wxID_SELECTALL, wxString( wxT("&Select All\tCtrl+A") ) , wxEmptyString, wxITEM_NORMAL );
	edit_menu_tab->Append( edit_menu_select_all );

	menubar->Append( edit_menu_tab, wxT("Edit") );

	help_menu_tab = new wxMenu();
	wxMenuItem* help_menu_about;
	help_menu_about = new wxMenuItem( help_menu_tab, wxID_ABOUT, wxString( wxT("&About\tF1") ) , wxT("Show about dialog"), wxITEM_NORMAL );
	help_menu_tab->Append( help_menu_about );

	menubar->Append( help_menu_tab, wxT("Help") );

	this->SetMenuBar( menubar );


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CHAR, wxKeyEventHandler( Spark::math_sync_scrollbar ) );
	math_input->Connect( wxEVT_COMMAND_RICHTEXT_CHARACTER, wxCommandEventHandler( Spark::math_input_evt ), NULL, this );
	math_input->Connect( wxEVT_COMMAND_RICHTEXT_DELETE, wxCommandEventHandler( Spark::math_input_evt ), NULL, this );
	math_input->Connect( wxEVT_COMMAND_RICHTEXT_RETURN, wxCommandEventHandler( Spark::math_input_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
}

Spark::~Spark()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CHAR, wxKeyEventHandler( Spark::math_sync_scrollbar ) );
	math_input->Disconnect( wxEVT_COMMAND_RICHTEXT_CHARACTER, wxCommandEventHandler( Spark::math_input_evt ), NULL, this );
	math_input->Disconnect( wxEVT_COMMAND_RICHTEXT_DELETE, wxCommandEventHandler( Spark::math_input_evt ), NULL, this );
	math_input->Disconnect( wxEVT_COMMAND_RICHTEXT_RETURN, wxCommandEventHandler( Spark::math_input_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );
	math_scrollbar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Spark::math_scroll_evt ), NULL, this );

}
