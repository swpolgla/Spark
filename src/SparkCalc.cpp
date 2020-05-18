#include "SparkCalc.h"

SparkCalc::SparkCalc( wxWindow* parent )
:
Spark( parent, -1, "Spark Calc" )
{
    math_input -> GetStyle(0, Standard_Input_Style);
    
    Default_Input_Color = Standard_Input_Style.GetTextColour();
    
    Input_Variable_Color.Set(52, 195, 235);
    
    Answer_Color.Set(103, 230, 0);
    
    math_output -> GetCaret() -> Hide();
    
    math_input -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    math_output -> ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    
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

/**
    This is run every time text is input into the math_input RichTextCtrl. For every line in the text box
    it builds an OperationTree, evaluates it, and places the output in the same line of the math_output RichTextCtrl.
 */
void SparkCalc::math_input_evt(wxCommandEvent& WXUNUSED(event)) {
    Operations::OperationTree tree;
    
    this -> math_output -> Clear();
    this -> math_output -> ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_RIGHT);
    
    std::map<std::string, double> variableLookupTable;
    std::string operationValues = "^*/+-.1234567890";
    std::string alphabeticalValues = "abcdefghijklmnopqrstuvwxyz";
    alphabeticalValues.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    long lineStart = 0;
    int lineCount = math_input -> GetNumberOfLines();
    for(int x = 0; x < lineCount; x++) {
        std::string originalLine = std::string(this -> math_input -> GetLineText(x));
        std::string lineEval = std::string(this -> math_input -> GetLineText(x));
        lineEval.erase(remove_if(lineEval.begin(), lineEval.end(), isspace), lineEval.end());
        
        //Applies the default text style to the entire line inside of the math_input RichTextCtrl.
        //If you skip overriding the style every time, the variable text colors will begin to "bleed"
        //out into surrounding lines and input which is bad.
        Standard_Input_Style.SetTextColour(Default_Input_Color);
        math_input -> SetStyle(lineStart, lineStart + math_input -> GetLineText(x).length(), Standard_Input_Style);
        
        if(lineEval.length() == 0) {
            math_output -> AppendText('\n');
            lineStart++;
            continue;
        }
        
        double eval = 0;
        
        //This bit determines if the line is intended to be a variable
        //If it's intended to be a variable it will strip the variable naming
        //out of the string, leaving only the math input behind, calculate
        //the result of the math input, and add the variable name/result to the
        //variableLookupTable.
        //In the event an existing variable is used, that variable name is replaced
        //with it's numerical value in the line string from the lookup table.
        std::string varName = "";
        size_t equalLocation = lineEval.find_first_of('=');
        if(equalLocation != std::string::npos) {
            if(lineEval.find_first_of(alphabeticalValues) < equalLocation) {
                varName = lineEval.substr(0, equalLocation);
                lineEval.erase(0, equalLocation + 1);
            }
            
            //Add text color to input box as needed
            size_t inputBoxEqualLocation = originalLine.find_first_of('=');
            Standard_Input_Style.SetTextColour(Input_Variable_Color);
            math_input -> SetStyle(lineStart, lineStart + inputBoxEqualLocation, Standard_Input_Style);
        }
        
        std::map<std::string, double>::iterator it;
        for(it = variableLookupTable.begin(); it != variableLookupTable.end(); it++) {
            size_t variableLocation = lineEval.find(it -> first);
            while(variableLocation != std::string::npos) {
                lineEval.erase(variableLocation, it -> first.length());
                lineEval.insert(variableLocation, std::to_string(it -> second));
                variableLocation = lineEval.find(it -> first);
            }
        }
        
        try {
            eval = tree.evaluate(lineEval);
        } catch (int i) {
            return;
        }
        
        if(varName.length() > 0) {
            variableLookupTable.insert(std::pair<std::string, double>(varName, eval));
        }
        
        std::string line = std::to_string(eval);
        line.erase(line.find_last_not_of('0') + 1);
        if(line[line.length() - 1] == '.') {
            line.erase(line.length() - 1);
        }
        
        wxString lineString(line);
        math_output -> BeginTextColour(Answer_Color);
        math_output -> WriteText(line);
        math_output -> EndTextColour();
        math_output -> AppendText('\n');
        lineStart += originalLine.length() + 1;
    }
    math_output -> Remove(math_output -> GetLastPosition() - 1, math_output -> GetLastPosition());
    math_output -> GetCaret() -> Hide();
    
    sync_all_scrollbars();
}

void SparkCalc::sync_all_scrollbars() {
    math_input -> Freeze();
    math_output -> Freeze();
    
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
    
    math_input -> Thaw();
    
    
    math_output->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
    math_output->Thaw();
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
wxEND_EVENT_TABLE()
