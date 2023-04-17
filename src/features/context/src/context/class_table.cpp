#include <context/class_table.hpp>

ClassInfo::ClassInfo(const std::map<std::string, std::unique_ptr<SymbolInfo>> &info)
{
    for (const auto &p : info)
    {
        this->info.emplace(p.first, p.second->clone());
    }
}

ClassInfo::ClassInfo(std::map<std::string, std::unique_ptr<SymbolInfo>> &&info)
{
    this->info = std::move(info);
}

ClassInfo::ClassInfo(const ClassInfo &other)
{
    for (const auto &p : other.info)
    {
        this->info.emplace(p.first, p.second->clone());
    }
}

ClassInfo::ClassInfo(ClassInfo &&other)
{
    this->info = std::move(other.info);
}

void ClassInfo::addProperty(const std::string &name, const std::unique_ptr<SymbolInfo> &symbol)
{
    this->info.emplace(name, symbol->clone());
}

void ClassInfo::addProperty(const std::string &name, std::unique_ptr<SymbolInfo> &&symbol)
{
    this->info.emplace(name, std::move(symbol));
}

ClassInfo &ClassInfo::operator=(const ClassInfo &other)
{
    if (this != &other)
    {
        for (const auto &p : other.info)
        {
            this->info.emplace(p.first, p.second->clone());
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