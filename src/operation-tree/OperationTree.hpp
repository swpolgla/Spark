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
#include <algorithm>
#include <vector>
#include "nodes/OperationNode.hpp"
#include "nodes/MathNode.hpp"
#include "nodes/ValueNode.hpp"

namespace Operations {
    class OperationTree {
    private:
        /** The head node of the tree */
        OperationNode *head = nullptr;
        
        /**
            Accepts a string as input and recursively builds a tree representation of it.
            Each node in the tree is either a numerical value or a mathematical operation.
            All leaf nodes will be ValueNodes.
            The operations are distributed throughout the tree based on their priority with respect
            PEMDAS. The lowest priority operation is the root node for example.
            @param _input the string to build a tree of
         */
        void buildTree(std::string _input);
        void clean();
        
    public:
        ~OperationTree();
        
        /**
            Accepts a string as input, builds a tree structure from the input, and evaluates the tree.
            @param _input the string of math input
            @return the evaluation of _input as a double
         */
        double evaluate(std::string _input);
    };
}

#endif /* OperationTree_hpp */
