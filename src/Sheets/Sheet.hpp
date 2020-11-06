//
//  Sheet.hpp
//  Spark
//
//  Created by Steven Polglase on 7/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef Sheet_hpp
#define Sheet_hpp

#include <map>
#include <stdio.h>
#include <string>
#include <vector>
#include "../operation-tree/OperationTree.hpp"

namespace Sheets {
    class Sheet {
        private:
            /** This is the temporary map of all variables defined by the user in the current sheet.
                The key is the name of the variable, the value is the numerical value of the variable.
                The map is sorted in descending order, so that variable names that are sub strings of
                other variable names will function properly.
             */
            std::map<std::wstring, double, std::greater<std::wstring>> variables;
        
        public:
            /** Accepts the latest input from the user, and recalculates all lines on the Sheet.
                @return a fully formatted string of answers separated by line to be inserted into the math_output text box.
             */
            std::wstring UpdateSheet(const std::vector<std::wstring> _lines);
    };
}

#endif /* Sheet_hpp */
