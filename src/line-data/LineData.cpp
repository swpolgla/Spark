//
//  LineData.cpp
//  Spark
//
//  Created by Steven Polglase on 7/8/20.
//  Copyright © 2020 Steven Polglase. All rights reserved.
//

#include "LineData.hpp"

using namespace Sheets;

std::string LineData::GetLine() {
    return line;
}

void LineData::SetLine(const std::string newLine) {
    if(newLine.find_first_of('\n') != std::string::npos) {
        throw 31;
    }
    line = newLine;
}

long LineData::GetLineNumber() {
    return lineNumber;
}

void LineData::SetLineNumber(long newLineNumber) {
    lineNumber = newLineNumber;
}

void LineData::AddDependent(const long dependent) {
    if(dependent < 0) {
        throw 31;
    }
    dependents.insert(dependent);
}

void LineData::ClearDependents() {
    dependents.clear();
}

const std::set<long> LineData::GetDependents() {
    return dependents;
}

std::string LineData::GetLineVariable() {
    return lineVariable;
}

void LineData::SetLineVariable(const std::string newVariable) {
    lineVariable = newVariable;
}

double LineData::GetLineValue() {
    return lineValue;
}

void LineData::SetLineValue(const double newValue) {
    lineValue = newValue;
}
