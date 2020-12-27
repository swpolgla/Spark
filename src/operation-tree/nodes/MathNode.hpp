/**
 @file MathNode.hpp
 An implementation of the OperationNode class that evaluates mathematical operations.
*/

#ifndef MathNode_hpp
#define MathNode_hpp

#include <math.h>
#include "OperationNode.hpp"

/**
    These represent all the types of mathematical operations that the calculator can perform.
    This will likely be expanded in the future.
 */
enum OperationType { parentheses, exponent, multiplication, division, addition, subtraction, sine, cosine, tangent, sineh, cosineh, tangenth };

namespace Operations {
    class MathNode : public OperationNode {
    private:
        OperationType type;
        
    public:
        
        /** Constructs a new MathNode for a specific mathematical operation. */
        MathNode(OperationType _type);
        
        /** Updates the left child of the MathNode. */
        void setLeft(OperationNode* _left);
        
        /** Updates the right child of the MathNode. */
        void setRight(OperationNode* _right);
        
        /** Performs the mathematical operation specified by "type" to one or both of the child nodes. */
        double evaluate();
    };
}

#endif /* MathNode_hpp */
