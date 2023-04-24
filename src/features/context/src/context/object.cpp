#include <context/object.hpp>
#include <iostream>

bool matchType(const valueType &value, typeInfo &type)
{
    return true;
}

objectType::objectType()
    : className(),
      parameters() {}

objectType::objectType(const std::string &className, const std::map<std::string, valueType> parameters)
    : className(className),
      parameters(parameters) {}

objectType::objectType(const objectType &other)
    : className(other.className),
      parameters(other.parameters) {}

objectType::objectType(objectType &&other)
    : className(std::move(other.className)),
      parameters(std::move(other.parameters)) {}

objectType &objectType::operator=(const objectType &other)
{
    if (this != &other)
    {
        this->className = other.className;
        this->parameters = other.parameters;
    }
    return *this;
}

objectType &objectType::operator=(objectType &&other)
{
    if (this != &other)
    {
        this->className = std::move(other.className);
        this->parameters = std::move(other.parameters);
    }
    return *this;
}

std::string getTypeString(const typeInfo &type)
{
    if (std::holds_alternative<std::string>(type))
    {
        return std::get<std::string>(type);
    }
    return std::get<ClassTypeInfo>(type).className;
}

std::ostream &operator<<(std::ostream &out, objectType &a)
{
    out << "<";
    out << a.className;
    out << ">";
    out << "( ";
    for (auto params : a.parameters)
    {
        out << params.first << " : " << params.second << ",";
    }
    out << ")";
    return out;
}

std::ostream &operator<<(std::ostream &out, const valueType &value)
{
    overload print_overload{
        [&out](const std::shared_ptr<objectType> &a)
        {
            out << "<";
            out << a->className;
            out << ">";
            out << "( ";
            for (auto params : a->parameters)
            {
                out << params.first << " : " << params.second << ",";
            }
            out << ")";
        },
        [&out](auto &a)
        { out << a; }};

    std::visit(print_overload, value);
    return out;
}

std::istream &operator>>(std::istream &in, valueType &value)
{
    overload input_overload{
        [&in](std::shared_ptr<objectType> &a)
        { throw "object input cannot be taken"; },
        [&in](auto &a)
        { in >> a; }};

    std::visit(input_overload, value);
    return in;
}