//
//  Sheet.cpp
//  Spark
//
//  Created by Steven Polglase on 7/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "Sheet.hpp"

using namespace Sheets;

static bool replaceAll(std::string& source, const std::string& from, const std::string& to)
{
    bool replaced = false;
    
    std::string newString;
    newString.reserve(source.length());

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while(std::string::npos != (findPos = source.find(from, lastPos)))
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

std::string Sheet::UpdateSheet(const std::vector<std::string> _lines) {
    if(_lines.size() > lines.size()) {
        for(int x = 0; x < _lines.size() - lines.size(); x++) {
            LineData *data = new LineData();
            lines.push_back(data);
        }
    }
    
    std::set<long> dirtyLines;
    
    for(int x = 0; x < lines.size(); x++) {
        bool lineDirty = false;
        if(lines[x] -> GetLine().size() != _lines[x].size() || lines[x] -> GetLine().compare(_lines[x]) != 0) {
            //It's reasonable to assume whenever the line from the last iteration
            //and the latest line after the user's input don't match, and there are
            //more stored lines, than real lines, that the user just deleted a line(s).
            if(lines.size() > _lines.size()) {
                lines.erase(lines.begin() + x);
                for(int y = x; y < lines.size(); y++) {
                    lines[y] -> SetLineNumber(y);
                }
                x--;
                continue;
            }
            lineDirty = true;
        }
        if(dirtyLines.count(x) > 0 || lineDirty) {
            lines[x] -> SetLine(_lines[x]);
            dirtyLines.insert(x);
            for(auto e : lines[x] -> GetDependents()) {
                dirtyLines.insert(e);
            }
        }
    }
    
    for(auto e : dirtyLines) {
        lines[e] -> SetLineNumber(e);
        RebuildLine(lines[e]);
    }
    
    std::string output;
    
    for(int x = 0; x < lines.size(); x++) {
        output += std::to_string(lines[x] -> GetLineValue()) + '\n';
    }
    
    return output;
}

void Sheet::RebuildLine(LineData* _line) {
    //This is the "working copy" of the line.
    //Variable naming etc will be stripped from it.
    std::string line = _line -> GetLine();
    
    std::string varName = "";
    size_t equalLocation = line.find_first_of('=');
    if(equalLocation != std::string::npos) {
        if(equalLocation > 0) {
            varName = line.substr(0, equalLocation);
            line.erase(0, equalLocation + 1);
        }
    }
    
    for(auto e : variables) {
        if(_line -> GetLineNumber() > e.second) {
            bool replaced = replaceAll(line, e.first, std::to_string(lines[e.second] -> GetLineValue()));
            if(replaced) {
                lines[e.second] -> AddDependent(_line -> GetLineNumber());
            }
        }
    }
    
    Operations::OperationTree tree;
    double value = 0;
    try {
        value = tree.evaluate(line);
    } catch(int i) {
        //Do Nothing
    }
    _line -> SetLineValue(value);
    
    if(varName.length() > 0) {
        variables.insert(std::pair<std::string, long>(varName, _line -> GetLineNumber()));
    }
}
