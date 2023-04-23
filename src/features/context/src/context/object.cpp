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
    return std::get<classTypeInfo>(type).className;
}

std::ostream &operator<<(std::ostream &out, const valueType &value)
{
    overload print_overload{
        [&out](objectType &a)
        { out << "object cannot be printed"; },
        [&out](auto &a)
        { std::cout << a; }};

    std::visit(print_overload, value);
    return out;
}