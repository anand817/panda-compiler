#include <utils/nodes.hpp>

// all constructor definitions

TypeNode::TypeNode(const typeInfo &type) : type(type) {}
TypeNode::TypeNode(typeInfo &&type) : type(std::move(type)) {}

void TypeNode::print(std::string prefix)
{
    std::cout << prefix << "Type Node with type ";
    if (std::holds_alternative<std::string>(type))
    {
        std::cout << std::get<std::string>(type);
    }
    else
    {
        std::cout << std::get<classTypeInfo>(type).className;
    }
    std::cout << std::endl;
}

IdentifierNode::IdentifierNode(const std::string &name) : name(name) {}

void IdentifierNode::print(std::string prefix)
{
    std::cout << prefix << "Identifier Node with name: " << name << std::endl;
}

ValueNode::ValueNode(const std::string &type, const valueType &value) : type(type), value(value) {}

ValueNode::ValueNode(const std::string &type, const char *raw_value) : type(type)
{
    if (type == INT_TYPE)
    {
        value = atoi(raw_value);
    }
    else if (type == BOOL_TYPE)
    {
        if (strcmp(raw_value, "true") == 0)
        {
            value = true;
        }
        else
        {
            value = false;
        }
    }
    else if (type == FLOAT_TYPE)
    {
        value = (float)atof(raw_value);
    }
    else if (type == CHAR_TYPE)
    {
        value = raw_value[1];
    }
    else if (type == STRING_TYPE)
    {
        value = std::string(raw_value);
    }
    else
    {
        throw "invalid type";
    }
}

void ValueNode::print(std::string preifx)
{
    std::cout << preifx << "Value Node with type " << type << " and value ";
    if (type == INT_TYPE)
    {
        std::cout << std::get<int>(value);
    }
    else if (type == BOOL_TYPE)
    {
        std::cout << std::get<bool>(value);
    }
    else if (type == FLOAT_TYPE)
    {
        std::cout << std::get<float>(value);
    }
    else if (type == CHAR_TYPE)
    {
        std::cout << std::get<char>(value);
    }
    else if (type == STRING_TYPE)
    {
        std::cout << std::get<std::string>(value);
    }
    else
    {
        std::cout << "invalid type of data";
    }

    std::cout << std::endl;
}