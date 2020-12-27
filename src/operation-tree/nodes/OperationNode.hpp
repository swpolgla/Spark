/**
 @file OperationNode.hpp
 A virtual class that defines some shared methods for nodes within the OperationTree class.
*/

#ifndef OperationNode_hpp
#define OperationNode_hpp

#include <stdio.h>

namespace Operations {
    class OperationNode {
    private:
        
        /** The left child of the node */
        OperationNode *left = nullptr;
        
        /** The right child of the node */
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
