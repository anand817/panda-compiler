#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include <map>
#include <context/symbol_table.hpp>

class ClassInfo
{
public:
    std::map<std::string, std::unique_ptr<SymbolInfo>> info;

    ClassInfo(const std::map<std::string, std::unique_ptr<SymbolInfo>> &info);
    ClassInfo(std::map<std::string, std::unique_ptr<SymbolInfo>> &&info);
    ClassInfo(const ClassInfo &other);
    ClassInfo(ClassInfo &&other);

    void addProperty(const std::string &name, const std::unique_ptr<SymbolInfo> &symbol);
    void addProperty(const std::string &name, std::unique_ptr<SymbolInfo> &&symbol);

    ClassInfo &operator=(const ClassInfo &other);
    ClassInfo &operator=(ClassInfo &&other);
};

#endif // CLASS_INFO_H