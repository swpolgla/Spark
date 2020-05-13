//
//  MathNode.hpp
//  spark-calc
//
//  Created by Steven Polglase on 5/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef MathNode_hpp
#define MathNode_hpp

#include <math.h>
#include "OperationNode.hpp"

enum OperationType { exponent, multiplication, division, addition, subtraction };

namespace Operations {
    class MathNode : public OperationNode {
    private:
        OperationType type;
        
    public:
        MathNode(OperationType _type);
        double evaluate();
        void setLeft(OperationNode* _left);
        void setRight(OperationNode* _right);
    };
}

#endif /* MathNode_hpp */
