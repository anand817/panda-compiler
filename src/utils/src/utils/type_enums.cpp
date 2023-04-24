#include <enums/type_enum.hpp>
#include <iostream>

valueType getDefaultValue(const std::string type)
{
    valueType value;
    if (type == INT_TYPE)
    {
        return value = 0;
    }
    else if (type == FLOAT_TYPE)
    {
        return value = (float)0.0;
    }
    else if (type == CHAR_TYPE)
    {
        return value = ' ';
    }
    else if (type == BOOL_TYPE)
    {
        return value = false;
    }
    else if (type == STRING_TYPE)
    {
        return value = std::string("");
    }
    throw("no default value got type " + type);
}