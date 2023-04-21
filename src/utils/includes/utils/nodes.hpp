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
private:
    void assignType(const valueType &value);

public:
    valueType value;
    typeInfo type;

    ValueNode();
    ValueNode(const valueType &value);
    ValueNode(const typeInfo &type, const valueType &value);
    ValueNode(const std::string &type, const char *raw_value);

    // assigns the value as well as type
    void assignValue(const valueType &value);
    void print(std::string prefix);
};

#endif // UTILS_NODES_H