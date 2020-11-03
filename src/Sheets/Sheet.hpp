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
#include "../operation-tree/OperationTree.hpp"

namespace Sheets {
    class Sheet {
        private:
            std::map<std::wstring, double, std::greater<std::wstring>> variables;
        
        public:
            std::wstring UpdateSheet(const std::vector<std::wstring> _lines);
    };
}

#endif /* Sheet_hpp */
