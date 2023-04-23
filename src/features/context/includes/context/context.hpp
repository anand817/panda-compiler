#ifndef CONTEXT_H
#define CONTEXT_H

#include <map>
#include <vector>
#include <memory>
#include <context/symbol_table.hpp>
#include <enums/scope_type_enum.hpp>
#include <context/class_table.hpp>
#include <base/nodes.hpp>

class ContextHandler; // forward declaration to remove circuilar dependency
class BlockNode;

class Context
{
public:
    int id;
    SCOPE_TYPE scope_type;
    Node *node; // do not delete node on object destruction
    std::map<std::string, std::unique_ptr<SymbolInfo>> symbolTable;
    std::map<std::string, std::unique_ptr<ClassInfo>> classTable;

public:
    // constructors
    Context(int id, SCOPE_TYPE type, Node *const &node);
    Context(int id, const SCOPE_TYPE &type, Node *const &node, const std::map<std::string, std::unique_ptr<SymbolInfo>> &symbolTable);
    Context(int id, SCOPE_TYPE &&type, Node *const &node, std::map<std::string, std::unique_ptr<SymbolInfo>> &&symbolTable);
    Context(Context &&other);
    Context(const Context &other);

    // operator overloads
    Context &operator=(Context &&other);
    Context &operator=(const Context &other);

    // public methods
    // add or update symbol if already added
    void addSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data);
    void addSymbol(const std::string &identifier, const typeInfo &dataType, const std::vector<std::pair<std::string, typeInfo>> &parameterList, BlockNode *const &functionBlockNode);

    void addClass(const std::string &name, const classTypeInfo &info);
    void addClass(const std::string &name, classTypeInfo &&info);

    void print() const;

    friend class ContextHandler;
};

// TODO: learn about ways to remove circuilar dependency

#endif // CONTEXT_H