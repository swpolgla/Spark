#include "SparkCalc.h"

SparkCalc::SparkCalc( wxWindow* parent )
:
Spark( parent, -1, "Spark Calc" )
{
    math_input -> GetStyle(0, Standard_Input_Style);
    
    Default_Input_Color = Standard_Input_Style.GetTextColour();
    
    Input_Variable_Color.Set(52, 195, 235);
    
    Answer_Color.Set(103, 230, 0);
    
    Function_Color.Set(107, 154, 255);
    
    math_output -> GetCaret() -> Hide();
    
    math_input -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    math_output -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    
    //math_input -> EnableImages(false);
    //math_output -> EnableImages(false);
    
    math_input->Connect( wxEVT_SCROLLWIN_TOP, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_input->Connect( wxEVT_SCROLLWIN_BOTTOM, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    math_input->Connect( wxEVT_SCROLLWIN_LINEUP, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_input->Connect( wxEVT_SCROLLWIN_LINEDOWN, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    math_input->Connect( wxEVT_SCROLLWIN_PAGEUP, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_input->Connect( wxEVT_SCROLLWIN_PAGEDOWN, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    math_input->Connect( wxEVT_SCROLLWIN_THUMBTRACK, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_input->Connect( wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    
    math_input->Connect( wxEVT_KEY_DOWN, wxCharEventHandler( SparkCalc::math_sync_scrollbar ), NULL, this );
    
    math_output->Connect( wxEVT_SCROLLWIN_TOP, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_output->Connect( wxEVT_SCROLLWIN_BOTTOM, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    math_output->Connect( wxEVT_SCROLLWIN_LINEUP, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_output->Connect( wxEVT_SCROLLWIN_LINEDOWN, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    math_output->Connect( wxEVT_SCROLLWIN_PAGEUP, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_output->Connect( wxEVT_SCROLLWIN_PAGEDOWN, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    math_output->Connect( wxEVT_SCROLLWIN_THUMBTRACK, wxScrollEventHandler( SparkCalc::math_scroll_up_evt ), NULL, this );
    math_output->Connect( wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollEventHandler( SparkCalc::math_scroll_down_evt ), NULL, this );
    
    math_output->Connect( wxEVT_NAVIGATION_KEY, wxCharEventHandler( SparkCalc::math_sync_scrollbar ), NULL, this );
    
    math_scrollbar -> SetScrollbar(math_input -> GetScrollPos(wxVERTICAL), math_input -> GetScrollThumb(wxVERTICAL), math_input -> GetScrollRange(wxVERTICAL), math_input -> GetScrollPageSize(wxVERTICAL));
    math_scrollbar -> Disable();
}

void SparkCalc::math_scroll_evt(wxScrollEvent& event) {
    math_input -> GetScrollHelper() -> Scroll(0, event.GetPosition());
    math_output -> GetScrollHelper() -> Scroll(0, event.GetPosition());
}

void SparkCalc::math_scroll_up_evt(wxScrollEvent& event) {
    math_input -> GetScrollHelper() -> Scroll(0, math_scrollbar -> GetThumbPosition() - 1);
    math_output -> GetScrollHelper() -> Scroll(0, math_scrollbar -> GetThumbPosition() - 1);
    math_scrollbar -> SetThumbPosition(math_scrollbar -> GetThumbPosition() - 1);
}

void SparkCalc::math_scroll_down_evt(wxScrollEvent& event) {
    math_input -> GetScrollHelper() -> Scroll(0, math_scrollbar -> GetThumbPosition() + 1);
    math_output -> GetScrollHelper() -> Scroll(0, math_scrollbar -> GetThumbPosition() + 1);
    math_scrollbar -> SetThumbPosition(math_scrollbar -> GetThumbPosition() + 1);
}

void SparkCalc::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void SparkCalc::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to Spark Calculator!\n"
                    "\n"
                    "This is version 0.0.1a "
                    "running under %s.",
                    wxGetOsDescription()
                 ),
                 "Spark Calculator",
                 wxOK | wxICON_INFORMATION,
                 this);
}

void SparkCalc::OnCut(wxCommandEvent& event) {
    math_input -> OnCut(event);
    math_input_evt(event);
}
void SparkCalc::OnCopy(wxCommandEvent& event) {
    math_input -> OnCopy(event);
}
void SparkCalc::OnPaste(wxCommandEvent& event) {
    math_input -> OnPaste(event);
    math_input_evt(event);
}
void SparkCalc::OnUndo(wxCommandEvent& event) {
    math_input -> OnUndo(event);
    math_input_evt(event);
}
void SparkCalc::OnRedo(wxCommandEvent& event) {
    math_input -> OnRedo(event);
    math_input_evt(event);
}
void SparkCalc::OnSelectAll(wxCommandEvent& event) {
    math_input -> OnSelectAll(event);
}

/**
    This is run every time text is input into the math_input RichTextCtrl. For every line in the text box
    it builds an OperationTree, evaluates it, and places the output in the same line of the math_output RichTextCtrl.
 */
void SparkCalc::math_input_evt(wxCommandEvent& WXUNUSED(event)) {
    wxWindowUpdateLocker noUpdateInput(math_input);
    wxWindowUpdateLocker noUpdateOutput(math_output);
    
    std::vector<std::string> lines;
    for(int x = 0; x < math_input -> GetNumberOfLines(); x++) {
        lines.push_back(math_input -> GetLineText(x).ToStdString());
    }
    
    math_output -> Clear();
    
    math_output -> AppendText(wxString(sheet.UpdateSheet(lines)));
    
    sync_all_scrollbars();
}

void SparkCalc::sync_all_scrollbars() {
    wxWindowUpdateLocker noUpdateInput(math_input);
    wxWindowUpdateLocker noUpdateOutput(math_output);
    
    math_input -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);
    math_output->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);
    math_input -> AdjustScrollbars();
    math_output -> AdjustScrollbars();
    
    if(math_input -> GetScrollRange(wxVERTICAL) > 0) {
        math_scrollbar -> Enable();
        math_scrollbar -> SetScrollbar(math_input -> GetScrollPos(wxVERTICAL), math_input -> GetScrollThumb(wxVERTICAL), math_input -> GetScrollLines(wxVERTICAL), math_input -> GetScrollPageSize(wxVERTICAL));
    }
    else {
        math_scrollbar -> Disable();
    }
    math_output -> Scroll(0, math_scrollbar -> GetThumbPosition());
    
    
    math_input -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    
    math_output->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
}

void SparkCalc::math_sync_scrollbar(wxKeyEvent& event) {
    
    math_input -> OnChar(event);
    if(event.IsKeyInCategory(WXK_CATEGORY_ARROW) || event.IsKeyInCategory(WXK_CATEGORY_NAVIGATION)) {
        sync_all_scrollbars();
    }
}

wxBEGIN_EVENT_TABLE(SparkCalc, wxFrame)
    EVT_MENU(Spark_Quit,  SparkCalc::OnQuit)
    EVT_MENU(Spark_About, SparkCalc::OnAbout)
    EVT_MENU(wxID_CUT, SparkCalc::OnCut)
    EVT_MENU(wxID_COPY, SparkCalc::OnCopy)
    EVT_MENU(wxID_PASTE, SparkCalc::OnPaste)
    EVT_MENU(wxID_UNDO, SparkCalc::OnUndo)
    EVT_MENU(wxID_REDO, SparkCalc::OnRedo)
    EVT_MENU(wxID_SELECTALL, SparkCalc::OnSelectAll)
wxEND_EVENT_TABLE()
