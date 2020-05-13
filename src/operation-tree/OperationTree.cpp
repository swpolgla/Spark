//
//  OperationTree.cpp
//  spark-calc
//
//  Created by Steven Polglase on 5/7/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "OperationTree.hpp"

using namespace Operations;

OperationTree::~OperationTree() {
    clean();
}

static std::string replaceMathConstants(std::string _input) {
    std::map<std::string, double> constantsMap;
    constantsMap.insert(std::pair<std::string, double>("pi", M_PI));
    constantsMap.insert(std::pair<std::string, double>("e", M_E));
    
    std::map<std::string, double>::iterator it;
    for(it = constantsMap.begin(); it != constantsMap.end(); it++) {
        size_t variableLocation = _input.find(it -> first);
        if(variableLocation != std::string::npos) {
            _input.erase(variableLocation, it -> first.length());
            _input.insert(variableLocation, std::to_string(it -> second));
        }
    }
    
    return _input;
}

/**
    A helper method that recursively parses an input string in order to build it's equivalent operation tree.
    It parses input with respect to PEMDAS order of operations. The resulting tree contains ValueNodes
    as leaves (assuming the input is valid) and the highest priority operations appear at the lowest levels
    of the tree. The lowest priority operation in the input is the root node.
 */
static Operations::OperationNode* buildHelper(std::string input) {
    
    //If parentheses are detected, substring the things between them and build another tree out of it.
    std::size_t openCount = std::count(input.begin(), input.end(), '(');
    std::size_t closeCount = std::count(input.begin(), input.end(), ')');
    
    if(openCount != closeCount) {
        throw 31;
    }
    
    //Swap in math constants
    input = replaceMathConstants(input);
    
    std::stack<size_t> parStack;
    
    size_t last = -1;
    for(int x = 0; x < openCount; x++) {
        last = input.find('(', last + 1);
        parStack.push(last);
    }
    
    while(!parStack.empty()) {
        size_t start = parStack.top();
        parStack.pop();
        size_t end = input.find_first_of(')', start);
        
        OperationTree tree;
        double val = tree.evaluate(input.substr(start + 1, end - start - 1));
        input.erase(start, end - start + 1);
        input.insert(start, std::to_string(val));
    }
    
    //Begin parsing all inputs
    std::size_t subidx = input.find_last_of('-');
    std::size_t addidx = input.find_last_of('+');
    std::size_t dividx = input.find_last_of('/');
    std::size_t mulidx = input.find_last_of('*');
    std::size_t expidx = input.find_first_of('^');
    
    if(subidx != std::string::npos) {
        if(subidx > addidx || addidx == std::string::npos) {
            Operations::MathNode *sub = new Operations::MathNode(subtraction);
            sub -> setLeft(buildHelper(input.substr(0, subidx)));
            sub -> setRight(buildHelper(input.substr(subidx + 1)));
            return sub;
        }
    }
    if(addidx != std::string::npos) {
        Operations::MathNode *add = new Operations::MathNode(addition);
        add -> setLeft(buildHelper(input.substr(0, addidx)));
        add -> setRight(buildHelper(input.substr(addidx + 1)));
        return add;
    }
    if(dividx != std::string::npos) {
        if(dividx > mulidx || mulidx == std::string::npos) {
            Operations::MathNode *div = new Operations::MathNode(division);
            div -> setLeft(buildHelper(input.substr(0, dividx)));
            div -> setRight(buildHelper(input.substr(dividx + 1)));
            return div;
        }
    }
    if(mulidx != std::string::npos) {
        Operations::MathNode *mul = new Operations::MathNode(multiplication);
        mul -> setLeft(buildHelper(input.substr(0, mulidx)));
        mul -> setRight(buildHelper(input.substr(mulidx + 1)));
        return mul;
    }
    if(expidx != std::string::npos) {
        Operations::MathNode *exp = new Operations::MathNode(exponent);
        exp -> setLeft(buildHelper(input.substr(0, expidx)));
        exp -> setRight(buildHelper(input.substr(expidx + 1)));
        return exp;
    }
    else {
        Operations::ValueNode *value = new Operations::ValueNode();
        if(input.length() != 0) {
            try {
                value -> setValue(std::stod(input));
            } catch(const std::invalid_argument oor) {
                //Do Nothing, the input was invalid and should be treated like a 0.
            }
        }
        return value;
    }
    
    return nullptr;
}

void OperationTree::buildTree(std::string _input) {
    
    if(_input.empty()) {
        return;
    }
    
    _input.erase(remove_if(_input.begin(), _input.end(), isspace), _input.end());
    
    head = buildHelper(_input);
}

double OperationTree::evaluate(std::string _input) {
    clean();
    buildTree(_input);
    if(head != nullptr) {
        return head -> evaluate();
    }
    return 0;
}

void OperationTree::clean() {
    if(head != nullptr) {
        head -> clean();
        delete head;
        head = nullptr;
    }
}
