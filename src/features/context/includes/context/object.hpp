#ifndef OBJECT_H
#define OBJECT_H

#include <variant>
#include <map>
#include <memory>
#include <context/class_table.hpp>

struct objectType;

typedef std::variant<int, float, std::string, bool, char, objectType> valueType;

struct objectType
{
    std::map<std::string, valueType> object;
};

bool matchType(const valueType &value, typeInfo &type);

std::string getTypeString(const typeInfo &type);

#endif // OBJECT_H other.print();