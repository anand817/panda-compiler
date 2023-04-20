#include <context/class_table.hpp>

ClassInfo::ClassInfo(const classTypeInfo &info)
{
    this->info = info;
}

ClassInfo::ClassInfo(classTypeInfo &&info)
{
    this->info = std::move(info);
}

ClassInfo::ClassInfo(const ClassInfo &other)
{
    this->info = other.info;
}

ClassInfo::ClassInfo(ClassInfo &&other)
{
    this->info = std::move(other.info);
}

void ClassInfo::addProperty(const std::string &name, const typeInfo &type)
{
    this->info.propertyInfo.emplace(name, type);
}

ClassInfo &ClassInfo::operator=(const ClassInfo &other)
{
    if (this != &other)
    {
        this->info = other.info;
    }
    return *this;
}

ClassInfo &ClassInfo::operator=(ClassInfo &&other)
{
    if (this != &other)
    {
        this->info = std::move(other.info);
    }
    return *this;
}