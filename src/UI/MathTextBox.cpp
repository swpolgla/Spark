//
//  MathTextBox.cpp
//  Spark
//
//  Created by Steven Polglase on 11/9/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "MathTextBox.hpp"


void MathTextBox::Cut() {
    wxRichTextCtrl::Cut();
    parent->ProcessInput();
}

void MathTextBox::Paste() {
    wxRichTextCtrl::Paste();
    parent->ProcessInput();
}

void MathTextBox::Redo() {
    wxRichTextCtrl::Redo();
    parent->ProcessInput();
}

void MathTextBox::Undo() {
    wxRichTextCtrl::Undo();
    parent->ProcessInput();
}
