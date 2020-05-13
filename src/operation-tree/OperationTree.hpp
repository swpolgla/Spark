//
//  OperationTree.hpp
//  spark-calc
//
//  Created by Steven Polglase on 5/7/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef OperationTree_hpp
#define OperationTree_hpp

#include <stdio.h>
#include <iostream>
#include <stack>
#include <map>
#include <cmath>
#include "nodes/OperationNode.hpp"
#include "nodes/MathNode.hpp"
#include "nodes/ValueNode.hpp"

namespace Operations {
    class OperationTree {
    private:
        OperationNode *head = nullptr;
        void buildTree(std::string _input);
        void clean();
        
    public:
        ~OperationTree();
        double evaluate(std::string _input);
    };
}

#endif /* OperationTree_hpp */
