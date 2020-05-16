#include "SparkCalc.h"

SparkCalc::SparkCalc( wxWindow* parent )
:
Spark( parent, -1, "Spark Calc" )
{
    math_input -> GetStyle(0, Standard_Input_Style);
    
    Default_Input_Color = Standard_Input_Style.GetTextColour();
    
    Input_Variable_Color.Set(52, 195, 235);
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
void SparkCalc::math_input_evt(wxCommandEvent& event) {
    Operations::OperationTree tree;
    //std::cout << this -> math_input -> GetNumberOfLines() << std::endl;
    
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
        
        //Apply default text style to entire line
        Standard_Input_Style.SetTextColour(Default_Input_Color);
        math_input -> SetStyle(lineStart, lineStart + math_input -> GetLineText(x).length(), Standard_Input_Style);
        
        if(lineEval.length() == 0) {
            math_output -> AppendText('\n');
            lineStart++;
            continue;
        }
        
        double eval = 0;
        
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
        math_output -> BeginTextColour(wxColour(103, 230, 0));
        math_output -> WriteText(line);
        math_output -> EndTextColour();
        math_output -> AppendText('\n');
        
        lineStart += originalLine.length() + 1;
    }
}

wxBEGIN_EVENT_TABLE(SparkCalc, wxFrame)
    EVT_MENU(Spark_Quit,  SparkCalc::OnQuit)
    EVT_MENU(Spark_About, SparkCalc::OnAbout)
wxEND_EVENT_TABLE()
