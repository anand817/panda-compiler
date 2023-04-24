#include <utils/nodes.hpp>
#include <context/context_handler.hpp>

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
        std::cout << std::get<ClassTypeInfo>(type).className;
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

ValueNode::ValueNode(const ValueNode &other)
    : value(other.value),
      type(other.type) {}

void ValueNode::assignType(const valueType &value)
{
    // overload type_overload1{
    //     [this](int &a)
    //     { this->type = INT_TYPE; },
    //     [this](float &a)
    //     { this->type = FLOAT_TYPE; },
    //     [this](std::string &a)
    //     { this->type = STRING_TYPE; },
    //     [this](bool &a)
    //     { this->type = BOOL_TYPE; },
    //     [this](char &a)
    //     { this->type = CHAR_TYPE; },
    //     [this, &value](std::shared_ptr<objectType> &a)
    //     { this->type = std::get<std::shared_ptr<objectType>>(value)->info; }};

    switch (value.index())
    {
    case 0:
        type = INT_TYPE;
        break;
    case 1:
        type = FLOAT_TYPE;
        break;
    case 2:
        type = STRING_TYPE;
        break;
    case 3:
        type = BOOL_TYPE;
        break;
    case 4:
        type = CHAR_TYPE;
        break;
    case 5:
        type = std::get<std::shared_ptr<objectType>>(value)->info;
        // find class from class table and then assign the value
        break;
    default:
        std::cout << "type is not assigned ";
        break;
    }

    // std::visit(type_overload1, value);
}

void ValueNode::assignValue(const valueType &value)
{
    this->value = value;
    assignType(value);
}

void ValueNode::print(std::string preifx)
{
    std::cout << preifx << "Value Node with type " << getTypeString(type) << " and value " << value << std::endl;
}