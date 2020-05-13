//
//  ValueNode.hpp
//  spark-calc
//
//  Created by Steven Polglase on 5/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#ifndef ValueNode_hpp
#define ValueNode_hpp

#include "OperationNode.hpp"

namespace Operations {
    class ValueNode : public OperationNode {
    private:
        double value;
        
    public:
        ValueNode();
        void setValue(double _value);
        double evaluate();
    };
}

#endif /* ValueNode_hpp */
