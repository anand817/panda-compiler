#ifndef CONTEXT_H
#define CONTEXT_H

#include <context/symbol_table.hpp>
#include <map>
#include <vector>
#include <memory>

class ContextHandler; // forward declaration to remove circuilar dependency

class Context
{
    int id;
    std::map<std::string, std::unique_ptr<SymbolInfo>> symbolTable;

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
    void addSymbol(std::string identifier, std::string dataType, allType &data);
    void addSymbol(std::string identifier, std::string dataType, std::vector<std::string> &parameterList);

    friend class ContextHandler;
};

// TODO: learn about ways to remove circuilar dependency

#endif // CONTEXT_H