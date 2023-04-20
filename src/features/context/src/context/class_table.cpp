#include <context/class_table.hpp>

ClassInfo::ClassInfo(const propertyInfo &info)
{
    for (const auto &p : info)
    {
        this->info.emplace(p.first, p.second);
    }
}

ClassInfo::ClassInfo(propertyInfo &&info)
{
    this->info = std::move(info);
}

ClassInfo::ClassInfo(const ClassInfo &other)
{
    for (const auto &p : other.info)
    {
        this->info.emplace(p.first, p.second);
    }
}

ClassInfo::ClassInfo(ClassInfo &&other)
{
    this->info = std::move(other.info);
}

void ClassInfo::addProperty(const std::string &name, const std::string &type)
{
    this->info.emplace(name, type);
}

ClassInfo &ClassInfo::operator=(const ClassInfo &other)
{
    if (this != &other)
    {
        for (const auto &p : other.info)
        {
            this->info.emplace(p.first, p.second);
        }
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