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
#include <string>
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
        
        /**
           Parses an input string for the lowest priority addition or subtraction operation if present.
           Recursively builds a subtree of all inputs into the operation.
           @param input the string to parse
           @return the root node of the sub tree
        */
        Operations::OperationNode *ParseAdditionAndSubtraction(std::string &input, std::vector<int> &parDepthList);
        
        /**
           Parses an input string for the lowest priority multiplication or division operation if present.
           Recursively builds a subtree of all inputs into the operation.
           @param input the string to parse
           @return the root node of the sub tree
        */
        Operations::OperationNode *ParseMultiplicationAndDivision(const std::string &input, std::vector<int> &parDepthList);
        
        /**
           Parses an input string for the highest priority exponent operation if present. Recursively builds
           a subtree of all inputs into the operation.
           @param input the string to parse
           @return the root node of the sub tree
        */
        Operations::OperationNode *ParseExponents(const std::string &input, std::vector<int> &parDepthList);
        
        /**
           Parses an input string for any trig operations if present. Recursively builds a subtree
           of whatever is being input into the trig function and returns the root node of that subtree.
           @param input the string to parse
           @return the root node of the sub tree
        */
        Operations::OperationNode *ParseTrig(const std::string &input);
        
        OperationNode* buildHelper(std::string input);
        
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
