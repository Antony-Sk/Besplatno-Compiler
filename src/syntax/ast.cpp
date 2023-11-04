//
// Created by anton on 02.11.23.
//

#include "ast.h"

bool Type::operator==(const Type &other) const {
    return *generics == *other.generics and base == other.base;
}

std::string Type::toString() {
    if (generics == nullptr)
        return base;
    return base + "[" + generics->toString() + "]";
}

bool Types::operator==(const Types &other) const {
    if (types.size() != other.types.size())
        return false;
    return true;
}

std::string Types::toString() {
    if (types.empty())
        return "";
    std::string s;
    for (int i = 0; i < types.size() - 1; i++) {
        s += types[i]->toString() + ", ";
    }
    s += types.back()->toString();
    return s;
}
