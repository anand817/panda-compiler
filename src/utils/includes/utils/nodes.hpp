#ifndef UTILS_NODES_H
#define UTILS_NODES_H

#include <string>

// node deifinitions that doesn't need to run
// i.e. that does not have any actual code

// for types
class TypeNode
{
public:
    std::string type;

    TypeNode(const std::string &type);
};

// for operators
class TokenNode
{
public:
    std::string value;

    TokenNode(const std::string &value);
};

// for identifiers
class IdentifierNode
{
public:
    std::string name;

    IdentifierNode(const std::string &name);
};

// for rvalue
// update to support rvalue objects
class ValueNode
{
public:
    std::string type;
    std::string value;

    ValueNode(const std::string &type, const std::string &value);
};

#endif // UTILS_NODES_H