//
//  MathTextBox.cpp
//  Spark
//
//  Created by Steven Polglase on 11/9/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "MathTextBox.hpp"


static void StripClipboardNewline() {
    if(wxTheClipboard->Open()) {
        wxTextDataObject data;
        wxTheClipboard->GetData(data);
        std::wstring copiedString = data.GetText().ToStdWstring();
        if(copiedString[copiedString.length() - 1] == L'\n') {
            copiedString.erase(copiedString.length() - 1);
        }
        wxTheClipboard->SetData(new wxTextDataObject(wxString(copiedString)));
        wxTheClipboard->Close();
    }
}

void MathTextBox::Copy() {
    wxRichTextCtrl::Copy();
    
    StripClipboardNewline();
}

void MathTextBox::Cut() {
    wxRichTextCtrl::Cut();
    
    StripClipboardNewline();
    
    // MacOS handles clipboard events with ctrl keys correctly, but
    // Windows and Linux need a bit of extra help to update the UI.
#if defined(_WIN32) || defined(__linux__)
    parent->ProcessInput();
#endif
}

void MathTextBox::Paste() {
    wxRichTextCtrl::Paste();
    
    // MacOS handles clipboard events with ctrl keys correctly, but
    // Windows and Linux need a bit of extra help to update the UI.
#if defined(_WIN32) || defined(__linux__)
    parent->ProcessInput();
#endif
}

void MathTextBox::Redo() {
    wxRichTextCtrl::Redo();
    
    // MacOS handles clipboard events with ctrl keys correctly, but
    // Windows and Linux need a bit of extra help to update the UI.
#if defined(_WIN32) || defined(__linux__)
    parent->ProcessInput();
#endif
}

void MathTextBox::Undo() {
    wxRichTextCtrl::Undo();
    
    // MacOS handles clipboard events with ctrl keys correctly, but
    // Windows and Linux need a bit of extra help to update the UI.
#if defined(_WIN32) || defined(__linux__)
    parent->ProcessInput();
#endif
}
