#ifndef OBJECT_H
#define OBJECT_H

#include <variant>
#include <map>
#include <memory>

struct objectType;

typedef std::variant<int, float, std::string, bool, char, objectType> valueType;

struct objectType
{
    std::map<std::string, valueType> object;
};

#endif // OBJECT_H