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

ValueNode::ValueNode() {}

ValueNode::ValueNode(const typeInfo &type, const valueType &value) : type(type), value(value) {}

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
        // TODO: find class in class type and assign type to classInfoType
        throw "invalid type";
    }
}

ValueNode::ValueNode(const valueType &value) : value(value)
{
    assignType(value);
}

void ValueNode::assignType(const valueType &value)
{
    switch (value.index())
    {
    case 0:
        type = INT_TYPE;
        std::cout << "int assign for value " << std::get<int>(value);
        break;
    case 1:
        type = FLOAT_TYPE;
        std::cout << "float assign for value " << std::get<float>(value);
        break;
    case 2:
        type = STRING_TYPE;
        std::cout << "string assign for value " << std::get<std::string>(value);
        break;
    case 3:
        std::cout << "bool assign for value " << std::get<bool>(value);
        type = BOOL_TYPE;
        break;
    case 4:
        std::cout << "char assign for value " << std::get<char>(value);
        type = CHAR_TYPE;
        break;
    case 5:
        std::cout << "class type assign for value ";
        type = classTypeInfo();
        break;
    default:
        std::cout << "type is not assigned ";
        break;
    }

    std::cout << std::endl;
}

void ValueNode::assignValue(const valueType &value)
{
    std::cout << "assign value called" << std::endl;
    this->value = value;
    assignType(value);
}

void ValueNode::print(std::string preifx)
{
    std::cout << preifx << "Value Node with type " << getTypeString(type) << " and value ";

    // TODO: overload can be used
    if (getTypeString(type) == INT_TYPE)
    {
        std::cout << std::get<int>(value);
    }
    else if (getTypeString(type) == BOOL_TYPE)
    {
        std::cout << std::get<bool>(value);
    }
    else if (getTypeString(type) == FLOAT_TYPE)
    {
        std::cout << std::get<float>(value);
    }
    else if (getTypeString(type) == CHAR_TYPE)
    {
        std::cout << std::get<char>(value);
    }
    else if (getTypeString(type) == STRING_TYPE)
    {
        std::cout << std::get<std::string>(value);
    }
    else
    {
        std::cout << "invalid type of data";
    }

    std::cout << std::endl;
}