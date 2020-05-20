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
    setLeft(nullptr);
    setRight(nullptr);
    setValue(0);
    setType(value);
}
void ValueNode::setValue(double _value) {
    value = _value;
}
double ValueNode::evaluate() {
    return value;
}
