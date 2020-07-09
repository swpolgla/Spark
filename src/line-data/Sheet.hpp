//
//  Sheet.hpp
//  Spark
//
//  Created by Steven Polglase on 7/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef Sheet_hpp
#define Sheet_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <set>
#include <vector>
#include "LineData.hpp"
#include "../operation-tree/OperationTree.hpp"

namespace Sheets {
    class Sheet {
        private:
            std::vector<LineData*> lines;
            std::map<std::string, long> variables;
        
            void RebuildLine(LineData* _line);
        
        public:
            std::string UpdateSheet(const std::vector<std::string> _lines);
    };
}

#endif /* Sheet_hpp */
