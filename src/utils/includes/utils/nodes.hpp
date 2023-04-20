#ifndef UTILS_NODES_H
#define UTILS_NODES_H

#include <string>
#include <context/object.hpp>
#include <context/class_table.hpp>
#include <iostream>
#include <enums/type_enum.hpp>
#include <cstring>

// node deifinitions that doesn't need to run
// i.e. that does not have any actual code

// for types
class TypeNode
{
public:
    typeInfo type;

    TypeNode(const typeInfo &type);
    TypeNode(typeInfo &&type);
    void print(std::string prefix);
};

// for operators
class TokenNode
{
public:
    const char *value;
};

// for identifiers
class IdentifierNode
{
public:
    std::string name;

    IdentifierNode(const std::string &name);
    void print(std::string prefix);
};

// for rvalue
// update to support rvalue objects
class ValueNode
{
public:
    std::string type;
    valueType value;

    ValueNode(const std::string &type, const valueType &value);
    ValueNode(const std::string &type, const char *raw_value);
    void print(std::string prefix);
};

#endif // UTILS_NODES_H