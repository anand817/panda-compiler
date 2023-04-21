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

template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

bool matchType(const valueType &value, typeInfo &type);

std::string getTypeString(const typeInfo &type);

#endif // OBJECT_H other.print();