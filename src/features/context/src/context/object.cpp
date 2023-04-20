#include <context/object.hpp>

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