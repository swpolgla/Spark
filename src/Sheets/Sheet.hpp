//
//  Sheet.hpp
//  Spark
//
//  Created by Steven Polglase on 7/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef Sheet_hpp
#define Sheet_hpp

#include <cwctype>
#include <map>
#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include "../operation-tree/OperationTree.hpp"

namespace Sheets {
    class Sheet {
        public:
            Sheet();
        
            /** Checks if a variable name overlaps with any function names. Used by SparkCalc class. */
            bool BannedVariableNameCheck(std::wstring name);
            /** Finds the locations of function names within the line of text. Returns a pair. Pair represents <position_within_string, length_of_string_found> */
            std::vector<std::pair<size_t, size_t>> FunctionNameLocations(std::wstring line);
        
            /** Accepts the latest input from the user, and recalculates all lines on the Sheet.
                @return a fully formatted string of answers separated by line to be inserted into the math_output text box.
             */
            std::wstring UpdateSheet(const std::vector<std::wstring> _lines);
        
        private:
            /** This is the temporary map of all variables defined by the user in the current sheet.
                The key is the name of the variable, the value is the numerical value of the variable.
                The map is sorted in descending order, so that variable names that are sub strings of
                other variable names will function properly.
             */
            std::map<std::wstring, double, std::greater<std::wstring>> variables;
            std::set<std::wstring> functionNames;
    };
}

#endif /* Sheet_hpp */
