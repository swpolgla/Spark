//
//  MathTextBox.hpp
//  Spark
//
//  Created by Steven Polglase on 11/9/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef MathTextBox_hpp
#define MathTextBox_hpp
#pragma once
#include "wx/richtext/richtextctrl.h"
#include "../SparkCalc.h"

/** Implementing Spark */
class MathTextBox : public wxRichTextCtrl
{
public:
    MathTextBox(wxWindow *parent, wxWindowID id, const wxString &value,
               const wxPoint &pos, const wxSize &size, int style = 0)
        : wxRichTextCtrl(parent, id, value, pos, size, style)
    {
        
    }

    /** Special Cut method. Does the same thing as wxRichTextCtrl::Cut() but also calls ProcessInput() in parent. */
    void Cut() override;
    /** Special Paste method. Does the same thing as wxRichTextCtrl::Paste() but also calls ProcessInput() in parent. */
    void Paste() override;
    /** Special Redo method. Does the same thing as wxRichTextCtrl::Redo() but also calls ProcessInput() in parent. */
    void Redo() override;
    /** Special Undo method. Does the same thing as wxRichTextCtrl::Undo() but also calls ProcessInput() in parent. */
    void Undo() override;
    
    SparkCalc *parent;

private:

    void LogClipEvent(const wxString& what, wxClipboardTextEvent& event);
    
};


#endif /* MathTextBox_hpp */
