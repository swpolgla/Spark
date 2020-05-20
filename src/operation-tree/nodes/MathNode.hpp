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

enum OperationType { parentheses, exponent, multiplication, division, addition, subtraction };

namespace Operations {
    class MathNode : public OperationNode {
    private:
        OperationType type;
        
    public:
        virtual ~MathNode() {
            
        }
        MathNode(OperationType _type);
        void setLeft(OperationNode* _left);
        void setRight(OperationNode* _right);
        double evaluate();
    };
}

#endif /* MathNode_hpp */
