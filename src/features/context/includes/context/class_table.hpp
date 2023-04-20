#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include <map>
#include <context/symbol_table.hpp>

typedef std::map<std::string, std::string> propertyInfo;
class ClassInfo
{
public:
    propertyInfo info;

    ClassInfo(const propertyInfo &info);
    ClassInfo(propertyInfo &&info);
    ClassInfo(const ClassInfo &other);
    ClassInfo(ClassInfo &&other);

    void addProperty(const std::string &name, const std::string &type);

    ClassInfo &operator=(const ClassInfo &other);
    ClassInfo &operator=(ClassInfo &&other);
};

#endif // CLASS_INFO_H