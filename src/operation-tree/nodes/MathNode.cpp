//
//  MathNode.cpp
//  spark-calc
//
//  Created by Steven Polglase on 5/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "MathNode.hpp"
#include "ValueNode.hpp"

using namespace Operations;

MathNode::MathNode(OperationType _type) {
    setLeft(nullptr);
    setRight(nullptr);
    type = _type;
    setType(math);
}

double MathNode::evaluate() {
    if(!getLeft() || !getRight()) {
        throw 31;
    }
    
    double left = getLeft() -> evaluate();
    double right = getRight() -> evaluate();
    
    switch (type) {
        case parentheses:
            return left;
        case exponent:
            return pow(left, right);
        case multiplication:
            return left * right;
        case division:
            if(right == 0) {
                throw 31;
            }
            return left / right;
        case addition:
            return left + right;
        case subtraction:
            return left - right;
        default:
            throw 31;
    }
}

void MathNode::setLeft(OperationNode* _left) {
    OperationNode::setLeft(_left);
}
void MathNode::setRight(OperationNode* _right) {
    OperationNode::setRight(_right);
}
