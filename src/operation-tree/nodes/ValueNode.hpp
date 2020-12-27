/**
 @file ValueNode.hpp
 An implementation of the OperationNode class that stores numerical values.
*/

#ifndef ValueNode_hpp
#define ValueNode_hpp

#include "OperationNode.hpp"

namespace Operations {
    class ValueNode : public OperationNode {
    private:
        double value;
        
    public:
        /** Constructs a ValueNode with a default numerical value of 0. */
        ValueNode();
        
        /** Updates the numerical value of the node. */
        void setValue(double _value);
        
        /** Returns the numerical value of this node. */
        double evaluate();
    };
}

#endif /* ValueNode_hpp */
