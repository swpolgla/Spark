//
//  OperationNode.hpp
//  spark-calc
//
//  Created by Steven Polglase on 5/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef OperationNode_hpp
#define OperationNode_hpp

#include <stdio.h>

namespace Operations {
    class OperationNode {
    private:
        OperationNode *left = nullptr;
        OperationNode *right = nullptr;
        
    public:
        virtual ~OperationNode() {
            clean();
        }
        virtual double evaluate() = 0;
        
        virtual OperationNode* getLeft() {
            return left;
        }
        virtual OperationNode* getRight() {
            return right;
        }
        virtual void setLeft(OperationNode* _left) {
            left = _left;
        }
        virtual void setRight(OperationNode* _right) {
            right = _right;
        }
        
        virtual void clean() {
            delete left;
            delete right;
        }
    };
}

#endif /* OperationNode_hpp */
