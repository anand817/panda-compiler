#ifndef CONTEXT_H
#define CONTEXT_H

#include <context/symbol_table.hpp>
#include <context/class_table.hpp>
#include <map>
#include <vector>
#include <memory>

class ContextHandler; // forward declaration to remove circuilar dependency

class Context
{
    int id;
    std::map<std::string, std::unique_ptr<SymbolInfo>> symbolTable;
    std::map<std::string, std::unique_ptr<ClassInfo>> classTable;

public:
    // constructors
    Context(int id);
    Context(int id, const std::map<std::string, std::unique_ptr<SymbolInfo>> &symbolTable);
    Context(int id, std::map<std::string, std::unique_ptr<SymbolInfo>> &&symbolTable);
    Context(Context &&other);
    Context(const Context &other);

    // operator overloads
    Context &operator=(Context &&other);
    Context &operator=(const Context &other);

    // public methods
    // add or update symbol if already added
    void addSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data);
    void addSymbol(const std::string &identifier, const typeInfo &dataType, const std::vector<std::string> &parameterList);

    void updateSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data);

    void addClass(const std::string &name, const classTypeInfo &info);
    void addClass(const std::string &name, classTypeInfo &&info);

    void print() const;

    friend class ContextHandler;
};

// TODO: learn about ways to remove circuilar dependency

#endif // CONTEXT_H