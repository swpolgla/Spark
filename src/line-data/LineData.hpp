//
//  LineData.hpp
//  Spark
//
//  Created by Steven Polglase on 7/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef LineData_hpp
#define LineData_hpp

#include <stdio.h>
#include <string>
#include <set>

namespace Sheets {
class LineData {
    private:
        std::string line;
        long lineNumber;
        std::set<long> dependents;
        std::string lineVariable;
        double lineValue;
    
    public:
        std::string GetLine();
        void SetLine(const std::string newLine);
        long GetLineNumber();
        void SetLineNumber(long newLineNumber);
        void AddDependent(const long dependent);
        void ClearDependents();
        const std::set<long> GetDependents();
        std::string GetLineVariable();
        void SetLineVariable(const std::string newVariable);
        double GetLineValue();
        void SetLineValue(const double newValue);
    
    };
}

#endif /* LineData_hpp */
