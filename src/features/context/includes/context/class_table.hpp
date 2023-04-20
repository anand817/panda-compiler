#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include <map>
#include <context/symbol_table.hpp>

struct classTypeInfo;

typedef std::variant<std::string, classTypeInfo> typeInfo;

struct classTypeInfo
{
    std::string className;
    std::map<std::string, typeInfo> propertyInfo;
};

class ClassInfo
{
public:
    classTypeInfo info;

    ClassInfo(const classTypeInfo &info);
    ClassInfo(classTypeInfo &&info);
    ClassInfo(const ClassInfo &other);
    ClassInfo(ClassInfo &&other);

    void addProperty(const std::string &name, const typeInfo &type);

    ClassInfo &operator=(const ClassInfo &other);
    ClassInfo &operator=(ClassInfo &&other);
};

#endif // CLASS_INFO_H