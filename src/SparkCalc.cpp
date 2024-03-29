#include "SparkCalc.h"
#include "UI/MathTextBox.hpp"

SparkCalc::SparkCalc( wxWindow* parent )
:
Spark( parent, -1, "Spark Calc" )
{
    math_input -> GetStyle(0, Standard_Input_Style);
    
    Default_Input_Color = Standard_Input_Style.GetTextColour();
    
    Input_Variable_Color.Set(52, 195, 235);
    
    Banned_Input_Variable_Color.Set(201, 28, 28);
    
    Answer_Color.Set(103, 230, 0);
    
    Function_Color.Set(107, 154, 255);
    
    math_output -> GetCaret() -> Hide();
    
    math_input -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    math_output -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    
    // Prevents the program from crashing when text is dragged/dropped.
    wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);
    
    // These map all the possible scroll events to the custom events that handle scrolling the input/output
    // text boxes at the same time. It's ugly but necessary for this functionality
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
    
    math_input->parent = this;
    math_output->parent = this;
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
                    "This is version 0.0.3 "
                    "running under %s.",
                    wxGetOsDescription()
                 ),
                 "Spark Calculator",
                 wxOK | wxICON_INFORMATION,
                 this);
}

wxRichTextCtrl *SparkCalc::GetFocusedText() {
    wxWindow *win = FindFocus();
    return win ? wxDynamicCast(win, wxRichTextCtrl) : NULL;
}

void SparkCalc::OnCut(wxCommandEvent& event) {
    wxRichTextCtrl *text = GetFocusedText();
    if(text) {
        text -> OnCut(event);
        math_input_evt(event);
    }
}
void SparkCalc::OnCopy(wxCommandEvent& event) {
    wxRichTextCtrl *text = GetFocusedText();
    if(text)
        text -> OnCopy(event);
}
void SparkCalc::OnPaste(wxCommandEvent& event) {
    wxRichTextCtrl *text = GetFocusedText();
    if(text) {
        text -> OnPaste(event);
        math_input_evt(event);
    }
}
void SparkCalc::OnUndo(wxCommandEvent& event) {
    wxRichTextCtrl *text = GetFocusedText();
    if(text) {
        text -> Undo();
        ProcessInput();
    }
}
void SparkCalc::OnRedo(wxCommandEvent& event) {
    wxRichTextCtrl *text = GetFocusedText();
    if(text) {
        text -> Redo();
        ProcessInput();
    }
}
void SparkCalc::OnSelectAll(wxCommandEvent& event) {
    wxRichTextCtrl *text = GetFocusedText();
    if(text)
        text -> OnSelectAll(event);
}

void SparkCalc::SetVariableNameStyle() {
    math_input -> BeginSuppressUndo();
    long lineStart = 0;
    
    // The styles used for variable names are a slight modification of the default style
    wxRichTextAttr variableStyle(Standard_Input_Style);
    variableStyle.SetTextColour(Input_Variable_Color);
    variableStyle.SetFont(variableStyle.GetFont().MakeBold());
    wxRichTextAttr bannedVariableStyle(variableStyle);
    bannedVariableStyle.SetTextColour(Banned_Input_Variable_Color);
    bannedVariableStyle.SetFont(variableStyle.GetFont().MakeStrikethrough());
    
    for(long x = 0; x < math_input->GetNumberOfLines(); x++) {
        std::wstring line = math_input->GetLineText(x).ToStdWstring();
        
        size_t equal = line.find(L'=');
        if(equal != std::wstring::npos) {
            std::wstring varName = line.substr(0, equal);
            varName.erase(std::remove_if(varName.begin(), varName.end(), std::iswspace), varName.end());
            if(sheet.BannedVariableNameCheck(varName)) {
                math_input->SetStyle(lineStart, lineStart + equal, bannedVariableStyle);
            }
            else {
                math_input->SetStyle(lineStart, lineStart + equal, variableStyle);
            }
            math_input->SetStyle(lineStart + equal, lineStart + line.length() + 1, Standard_Input_Style);
        }
        else {
            math_input->SetStyle(lineStart, lineStart + line.length() + 1, Standard_Input_Style);
        }
        lineStart += line.length() + 1;
    }
    math_input -> EndSuppressUndo();
}

void SparkCalc::SetFunctionNameStyle() {
    math_input->BeginSuppressUndo();
    long lineStart = 0;
    
    wxRichTextAttr functionStyle(Standard_Input_Style);
    functionStyle.SetTextColour(Function_Color);
    functionStyle.SetFont(functionStyle.GetFont().MakeBold());
    
    for(long x = 0; x < math_input->GetNumberOfLines(); x++) {
        std::wstring line = math_input->GetLineText(x).ToStdWstring();
        
        std::vector<std::pair<size_t, size_t>> locations = sheet.FunctionNameLocations(line);
        for(int x = 0; x < locations.size(); x++) {
            math_input->SetStyle(lineStart + locations[x].first, lineStart + locations[x].first + locations[x].second, functionStyle);
        }
        
        lineStart += line.length() + 1;
    }
    
    
    math_input->EndSuppressUndo();
}

void SparkCalc::ProcessInput() {
    wxWindowUpdateLocker noUpdateInput(math_input);
    wxWindowUpdateLocker noUpdateOutput(math_output);
    
    std::vector<std::wstring> lines;
    for(int x = 0; x < math_input -> GetNumberOfLines(); x++) {
        std::wstring line = math_input -> GetLineText(x).ToStdWstring();
        lines.push_back(math_input -> GetLineText(x).ToStdWstring());
    }
    
    math_output -> Clear();
    math_output -> ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_RIGHT);
    
    math_output -> BeginTextColour(Answer_Color);
    math_output -> WriteText(wxString(sheet.UpdateSheet(lines)));
    math_output -> EndTextColour();
    math_output -> GetCaret() -> Hide();
    
    SetVariableNameStyle();
    SetFunctionNameStyle();
    
    sync_all_scrollbars();
}

/**
    This is run every time text is input into the math_input RichTextCtrl.
 */
void SparkCalc::math_input_evt(wxCommandEvent& WXUNUSED(event)) {
    ProcessInput();
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
