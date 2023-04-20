#include <utils/nodes.hpp>

// all constructor definitions

TypeNode::TypeNode(const std::string &type) : type(type) {}

IdentifierNode::IdentifierNode(const std::string &name) : name(name) {}

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
        value = raw_value[0];
    }
    else if (type == STRING_TYPE)
    {
        value = std::string(raw_value);
    }
    else if (type == VOID_TYPE)
    {
        throw "invalid type";
    }
    else
    {
        value = "object Type";
    }
}