//
//  Sheet.cpp
//  Spark
//
//  Created by Steven Polglase on 7/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "Sheet.hpp"

using namespace Sheets;

Sheet::Sheet() {
    functionNames.insert(L"sin");
    functionNames.insert(L"cos");
    functionNames.insert(L"tan");
    functionNames.insert(L"sinh");
    functionNames.insert(L"cosh");
    functionNames.insert(L"tanh");
}

bool Sheet::BannedVariableNameCheck(std::wstring name) {
    std::transform(name.begin(), name.end(), name.begin(), ::towlower);
    return functionNames.count(name) > 0 || name.empty();
}

std::vector<std::pair<size_t, size_t>> Sheet::FunctionNameLocations(std::wstring line) {
    std::vector<std::pair<size_t, size_t>> positions;
    
    size_t equal = line.find_first_of(L'=');
    if(equal == std::wstring::npos)
        equal = 0;
    for(auto const& x : functionNames) {
        size_t pos = line.find(x, equal);
        while(pos != std::wstring::npos) {
            bool valid = true;
            if(pos > 0 && std::iswalpha(line.at(pos - 1))) {
                valid = false;
            }
            else if (pos + x.length() >= line.length() || line.at(pos + x.length()) != L'(') {
                valid = false;
            }
            if(valid) {
                std::pair<size_t, size_t> pair(pos, x.length());
                positions.push_back(pair);
            }
            pos = line.find(x, pos + 1);
        }
    }
    return positions;
}

static bool replaceAll(std::wstring& source, const std::wstring& from, const std::wstring& to)
{
    bool replaced = false;
    
    std::wstring newString;
    newString.reserve(source.length());

    std::wstring::size_type lastPos = 0;
    std::wstring::size_type findPos;

    while(std::wstring::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
        replaced = true;
    }

    newString += source.substr(lastPos);

    source.swap(newString);
    return replaced;
}

static std::wstring formatDecimal(double value) {
    std::wstring result = std::to_wstring(value);
    
    size_t pos = result.find_last_not_of(L'0');
    result.erase(result[pos] == L'.' ? pos : pos + 1);
    
    return result;
}

std::wstring Sheet::UpdateSheet(const std::vector<std::wstring> _lines) {
    std::wstring output;
    variables.clear();
    
    Operations::OperationTree tree;
    for(int x = 0; x < _lines.size(); x++) {
        
        std::wstring line = _lines[x];
        line.erase(std::remove_if(line.begin(), line.end(), std::iswspace), line.end());
        
        size_t equal = line.find_first_of('=');
        if(equal != std::wstring::npos) {
            //Strip out the variable assignment and leave only the equation behind
            std::wstring varName = line.substr(0, equal);
            if(BannedVariableNameCheck(varName)) {
                output.push_back('\n');
                continue;
            }
            
            std::wstring equation = line.substr(equal + 1, line.length());
            replaceAll(equation, L"=", L"");
            
            for(auto const& x : variables) {
                replaceAll(equation, x.first, std::to_wstring(x.second));
            }
            
            double result = 0;
            try {
                result = tree.evaluate(equation);
            } catch(int i) {
                //Do nothing
            }
            
            variables.insert_or_assign(varName, result);
            
            output.append(formatDecimal(result));
        }
        else {
            for(auto const& x : variables) {
                replaceAll(line, x.first, std::to_wstring(x.second));
            }
            double result = 0;
            try {
                result = tree.evaluate(line);
            } catch(int i) {
                //Do nothing
            }
            if(result != 0) {
                output.append(formatDecimal(result));
            }
            
        }
        output.push_back('\n');
    }
    // Removes the last unnecessary newline from the output.
    output.erase(output.length() - 1);
    return output;
}
