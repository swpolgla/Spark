//
//  ValueNode.cpp
//  spark-calc
//
//  Created by Steven Polglase on 5/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "ValueNode.hpp"
#include "MathNode.hpp"

using namespace Operations;

ValueNode::ValueNode() {
    setValue(0);
    setType(value);
}
void ValueNode::setValue(double _value) {
    value = _value;
}
double ValueNode::evaluate() {
    return value;
}

void ValueNode::clean() {
    if(getLeft() != nullptr) {
        getLeft() -> clean();
        if(getLeft() -> getType() == value) {
            ValueNode *node = (ValueNode*)getLeft();
            delete node;
        }
        else {
            MathNode *node = (MathNode*)getLeft();
            delete node;
        }
    }
    if(getRight() != nullptr) {
        getRight() -> clean();
        if(getRight() -> getType() == value) {
            ValueNode *node = (ValueNode*)getRight();
            delete node;
        }
        else {
            MathNode *node = (MathNode*)getRight();
            delete node;
        }
    }
}
