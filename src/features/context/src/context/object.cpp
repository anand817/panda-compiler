#include <context/object.hpp>
#include <iostream>

bool matchType(const valueType &value, typeInfo &type)
{
    return true;
}

std::string getTypeString(const typeInfo &type)
{
    if (std::holds_alternative<std::string>(type))
    {
        return std::get<std::string>(type);
    }
    return std::get<ClassTypeInfo>(type).className;
}

std::ostream &operator<<(std::ostream &out, const valueType &value)
{
    overload print_overload{
        [&out](objectType &a)
        { throw "object input cannot be taken"; },
        [&out](auto &a)
        { out << a; }};

    std::visit(print_overload, value);
    return out;
}

std::istream &operator>>(std::istream &in, valueType &value)
{
    overload input_overload{
        [&in](objectType &a)
        { throw "object input cannot be taken"; },
        [&in](auto &a)
        { in >> a; }};

    std::visit(input_overload, value);
    return in;
}