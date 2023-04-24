#ifndef OBJECT_H
#define OBJECT_H

#include <variant>
#include <map>
#include <memory>
#include <context/class_table.hpp>

struct objectType;

typedef std::variant<int, float, std::string, bool, char, std::shared_ptr<objectType>> valueType;

struct objectType
{
    std::string className;
    std::map<std::string, valueType> parameters;

    objectType();
    objectType(const std::string &className, const std::map<std::string, valueType> parameters);
    objectType(const objectType &other);
    objectType(objectType &&other);

    objectType &operator=(const objectType &other);
    objectType &operator=(objectType &&other);

    friend std::ostream &operator<<(std::ostream &out, objectType &a);
};

std::ostream &operator<<(std::ostream &out, objectType &a);

template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

bool matchType(const valueType &value, typeInfo &type);

std::string getTypeString(const typeInfo &type);

std::ostream &operator<<(std::ostream &out, const valueType &value);
std::istream &operator>>(std::istream &in, valueType &value);

#endif // OBJECT_H other.print();