//
//  OperationTree.cpp
//  spark-calc
//
//  Created by Steven Polglase on 5/7/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "OperationTree.hpp"

using namespace Operations;

OperationTree::~OperationTree() {
    clean();
}

static void replaceAll(std::wstring& source, const std::wstring& from, const std::wstring& to)
{
    std::wstring newString;
    newString.reserve(source.length());

    std::wstring::size_type lastPos = 0;
    std::wstring::size_type findPos;

    while(std::wstring::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    newString += source.substr(lastPos);

    source.swap(newString);
}

static std::wstring replaceMathConstants(std::wstring _input) {
    std::map<std::wstring, double> constantsMap;
    constantsMap.insert(std::pair<std::wstring, double>(L"pi", M_PI));
    constantsMap.insert(std::pair<std::wstring, double>(L"e", M_E));
    
    std::map<std::wstring, double>::iterator it;
    for(it = constantsMap.begin(); it != constantsMap.end(); it++) {
        replaceAll(_input, it -> first, std::to_wstring(it -> second));
    }
    
    return _input;
}

void OperationTree::buildTree(std::wstring _input) {
    
    if(_input.empty()) {
        return;
    }
    
    //Delete spaces from input
    _input.erase(remove_if(_input.begin(), _input.end(), isspace), _input.end());
    
    //Replace % with multiplication equivalent
    if(_input.find('%') != std::wstring::npos) {
        replaceAll(_input, L"%", L"*0.01");
    }
    
    _input = replaceMathConstants(_input);
    
    head = buildHelper(_input);
}

OperationNode* OperationTree::ParseAdditionAndSubtraction(const std::wstring &input, std::vector<int> &parDepthList) {
    std::size_t subidx = input.find_last_of('-');
    while(subidx != std::wstring::npos && parDepthList[subidx] != 0) {
        subidx = input.find_last_of('-', subidx - 1);
    }
    
    std::size_t addidx = input.find_last_of('+');
    while(addidx != std::wstring::npos && parDepthList[addidx] != 0) {
        addidx = input.find_last_of('+', addidx - 1);
    }
    if(subidx != std::wstring::npos) {
        //This assists with determining if the dash is intended to be a negative sign
        //instead of a subtraction symbol. If it is intended to be a negative sign, then
        //it will likely have a non numerical character on the left side of it or one won't
        //exist at all.
        //Ex: "3*-2" "-1"
        //When it is known to be a negative sign, processing it should be deferred until after
        //other operations have been processed.
        if(subidx - 1 >= 0 && (std::isalnum(input[subidx - 1]) != 0 || input[subidx - 1] == ')')) {
            //In the order of operations, subtraction is the last operation that should be
            //performed. However this is incorrect in specific cases such as "1-2+3"
            //In cases of mixed addition and subtraction you must evaluate left to right.
            if(subidx > addidx || addidx == std::wstring::npos) {
                Operations::MathNode *sub = new Operations::MathNode(subtraction);
                sub -> setLeft(buildHelper(input.substr(0, subidx)));
                sub -> setRight(buildHelper(input.substr(subidx + 1)));
                return sub;
            }
        }
    }
    if(addidx != std::wstring::npos) {
        Operations::MathNode *add = new Operations::MathNode(addition);
        add -> setLeft(buildHelper(input.substr(0, addidx)));
        add -> setRight(buildHelper(input.substr(addidx + 1)));
        return add;
    }
    
    return nullptr;
}

Operations::OperationNode* OperationTree::ParseMultiplicationAndDivision(const std::wstring &input, std::vector<int> &parDepthList) {
    std::size_t dividx = input.find_last_of('/');
    while(dividx != std::wstring::npos && parDepthList[dividx] != 0) {
        dividx = input.find_last_of('/', dividx - 1);
    }
    
    std::size_t mulidx = input.find_last_of('*');
    while(mulidx != std::wstring::npos && parDepthList[mulidx] != 0) {
        mulidx = input.find_last_of('*', mulidx - 1);
    }
    if(dividx != std::wstring::npos) {
        if(dividx > mulidx || mulidx == std::wstring::npos) {
            Operations::MathNode *div = new Operations::MathNode(division);
            div -> setLeft(buildHelper(input.substr(0, dividx)));
            div -> setRight(buildHelper(input.substr(dividx + 1)));
            return div;
        }
    }
    if(mulidx != std::wstring::npos) {
        Operations::MathNode *mul = new Operations::MathNode(multiplication);
        mul -> setLeft(buildHelper(input.substr(0, mulidx)));
        mul -> setRight(buildHelper(input.substr(mulidx + 1)));
        return mul;
    }
    
    return nullptr;
}

OperationNode* OperationTree::ParseExponents(const std::wstring &input, std::vector<int> &parDepthList) {
    std::size_t expidx = input.find_first_of('^');
    while(expidx != std::wstring::npos && parDepthList[expidx] != 0) {
        expidx = input.find_first_of('^', expidx + 1);
    }
    if(expidx != std::wstring::npos) {
        Operations::MathNode *exp = new Operations::MathNode(exponent);
        exp -> setLeft(buildHelper(input.substr(0, expidx)));
        exp -> setRight(buildHelper(input.substr(expidx + 1)));
        return exp;
    }
    
    return nullptr;
}

OperationNode* OperationTree::ParseTrig(const std::wstring &input) {
    std::wstring trig = input.substr(0, 4);
    std::transform(trig.begin(), trig.end(), trig.begin(), ::tolower);
    Operations::MathNode *trigNode = nullptr;
    
    if(trig.length() < 3) {
        return nullptr;
    }
    
    //Parse trig functions of length 4
    if(trig.compare(L"sinh") == 0) {
        trigNode = new Operations::MathNode(sineh);
    }
    else if(trig.compare(L"cosh") == 0) {
        trigNode = new Operations::MathNode(cosineh);
    }
    else if(trig.compare(L"tanh") == 0) {
        trigNode = new Operations::MathNode(tangenth);
    }
    if(trigNode != nullptr) {
        //Math nodes can't have null children, but parentheses only care about the left child.
        //Creating an empty value node for the right child keeps things working as intended.
        Operations::ValueNode *empty = new Operations::ValueNode();
        trigNode -> setLeft(buildHelper(input.substr(4)));
        trigNode -> setRight(empty);
        return trigNode;
    }
    
    //Parse trig functions of length 3
    trig.erase(trig.end() - 1);
    if(trig.compare(L"sin") == 0) {
        trigNode = new Operations::MathNode(sine);
    }
    else if(trig.compare(L"cos") == 0) {
        trigNode = new Operations::MathNode(cosine);
    }
    else if(trig.compare(L"tan") == 0) {
        trigNode = new Operations::MathNode(tangent);
    }
    if(trigNode != nullptr) {
        //Math nodes can't have null children, but parentheses only care about the left child.
        //Creating an empty value node for the right child keeps things working as intended.
        Operations::ValueNode *empty = new Operations::ValueNode();
        trigNode -> setLeft(buildHelper(input.substr(3)));
        trigNode -> setRight(empty);
    }
    
    return trigNode;
}

/**
    A helper method that recursively parses an input string in order to build it's equivalent operation tree.
    It parses input with respect to PEMDAS order of operations. The resulting tree contains ValueNodes
    as leaves (assuming the input is valid) and the highest priority operations appear at the lowest levels
    of the tree. The lowest priority operation in the input is the root node.
 */
OperationNode* OperationTree::buildHelper(std::wstring input) {
    std::vector<int> parDepthList;
    int parDepth = 0;
    for(auto it = input.begin(); it != input.end(); it++) {
        if(*it == '(') {
            parDepth++;
        }
        else if(*it == ')') {
            parDepth--;
        }
        parDepthList.push_back(parDepth);
        
        // Check for close parentheses with no matching open parentheses. Ex: ")("
        if(parDepth < 0) {
            throw 31;
        }
    }
    // If parDepth is not 0 at the end of the string, then there aren't an equal number of
    // open/close parentheses or there is an open parentheses with no matching close parentheses.
    if(parDepth != 0) {
        throw 31;
    }
    
    //Begin parsing all inputs
    OperationNode* addsub = ParseAdditionAndSubtraction(input, parDepthList);
    if(addsub) {
        return addsub;
    }
    
    OperationNode* muldiv = ParseMultiplicationAndDivision(input, parDepthList);
    if(muldiv) {
        return muldiv;
    }
    
    OperationNode* exponent = ParseExponents(input, parDepthList);
    if(exponent) {
        return exponent;
    }
    
    OperationNode* trig = ParseTrig(input);
    if(trig) {
        return trig;
    }
    
    if(input.front() == '(' && input.back() == ')') {
        Operations::MathNode *par = new Operations::MathNode(parentheses);
        //Math nodes can't have null children, but parentheses only care about the left child.
        //Creating an empty value node for the right child keeps things working as intended.
        Operations::ValueNode *empty = new Operations::ValueNode();
        Operations::OperationNode *internal = buildHelper(input.substr(1, input.length() - 2));
        par -> setLeft(internal);
        par -> setRight(empty);
        return par;
    }
    else {
        Operations::ValueNode *value = new Operations::ValueNode();
        if(input.length() != 0) {
            try {
                value -> setValue(std::stod(input));
            } catch(const std::invalid_argument oor) {
                //Do Nothing, the input was invalid and should be treated like a 0.
            }
        }
        return value;
    }
    
    return nullptr;
}

double OperationTree::evaluate(std::wstring _input) {
    clean();
    
    std::size_t openCount = std::count(_input.begin(), _input.end(), '(');
    std::size_t closeCount = std::count(_input.begin(), _input.end(), ')');
    if(openCount != closeCount) {
        throw 31;
    }
    
    buildTree(_input);
    if(head != nullptr) {
        return head -> evaluate();
    }
    return 0;
}

void OperationTree::clean() {
    if(head != nullptr) {
        delete head;
        head = nullptr;
    }
}
