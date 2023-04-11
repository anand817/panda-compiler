#ifndef CONTEXT_H
#define CONTEXT_H

#include <context_handler.hpp>
#include <symbol_table.hpp>
#include <map>

class Context
{
    int id;
    std::map<std::string, SymbolInfo> symbolTable;

public:
    // constructors
    Context(int id);
    Context(int id, std::map<std::string, SymbolInfo> symbolTable);
    Context(Context &&other);
    Context(const Context &other);

    // operator overloads
    Context &operator=(Context &&other);
    Context &operator=(const Context &other);

    // public methods
    void addSymbol(std::string identifier, std::string dataType);

    friend class ContextHandler;
};

#endif // CONTEXT_H