#ifndef CONTEXT_HANDLER_H
#define CONTEXT_HANDLER_H

#include <context/context.hpp>
#include <context/class_table.hpp>
#include <iostream>
#include <stack>

class BlockNode; // forward declaration

// singleton class that handles context in the programme
class ContextHandler
{
    std::vector<Context> contextStack;
    std::vector<Context> poppedContextStack;
    int contextCounter;

private:
    ContextHandler();
    ContextHandler(ContextHandler &&other) = delete;
    ContextHandler(const ContextHandler &other) = delete;

public:
    Context &getContext();

public:
    static ContextHandler &getInstance();
    static void pushContext(SCOPE_TYPE scope_type);
    static void popContext();
    static void addSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data);
    static void addSymbol(const std::string &identifier, const typeInfo &dataType, const std::vector<std::pair<std::string, typeInfo>> &parameterList, BlockNode *const &functionBlockNode);
    static void updateSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data);
    static void addClass(const std::string &name, const classTypeInfo &info);
    static void addClass(const std::string &name, classTypeInfo &&info);
    static std::unique_ptr<SymbolInfo> &findSymbol(const std::string &identifier);
    static void printTable();

private:
    void pushContextImpl(SCOPE_TYPE scope_type);
    void popContextImpl();
    std::unique_ptr<SymbolInfo> &findSymbolImpl(const std::string &identifier);
    void printTableImpl();
};

#endif // CONTEXT_HANDLER_H