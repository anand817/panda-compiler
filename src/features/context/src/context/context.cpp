#include <context/context.hpp>
#include <iostream>

Context::Context(int id, const SCOPE_TYPE &type, Node *const &node, const std::map<std::string, std::unique_ptr<SymbolInfo>> &symbolTable)
    : id(id),
      scope_type(type),
      node(node),
      stop_processing(false)
{
    for (const auto &p : symbolTable)
    {
        this->symbolTable.emplace(p.first, p.second->clone());
    }
}

Context::Context(int id, SCOPE_TYPE &&type, Node *const &node, std::map<std::string, std::unique_ptr<SymbolInfo>> &&symbolTable)
    : id(id),
      scope_type(std::move(type)),
      symbolTable(std::move(symbolTable)),
      stop_processing(std::move(stop_processing)),
      node(node) {}

Context::Context(int id, SCOPE_TYPE type, Node *const &node)
    : id(id),
      scope_type(type),
      symbolTable(),
      stop_processing(false),
      node(node) {}

Context::Context(Context &&other)
    : id(other.id),
      symbolTable(std::move(other.symbolTable)),
      scope_type(std::move(other.scope_type)),
      stop_processing(std::move(other.stop_processing)),
      node(std::move(other.node)) {}

Context::Context(const Context &other)
    : id(other.id),
      scope_type(other.scope_type),
      node(other.node),
      stop_processing(std::move(other.stop_processing))
{
    std::cout << "after copying" << std::endl;
    node->print("");
    for (const auto &p : other.symbolTable)
    {
        this->symbolTable.emplace(p.first, p.second->clone());
    }
}

Context &Context::operator=(Context &&other)
{
    if (this != &other)
    {
        id = other.id;
        symbolTable = std::move(other.symbolTable);
        scope_type = std::move(other.scope_type);
        node = std::move(other.node);
        stop_processing = std::move(other.stop_processing);
    }

    return *this;
}

Context &Context::operator=(const Context &other)
{
    if (this != &other)
    {
        id = other.id;
        scope_type = other.scope_type;
        node = other.node;
        stop_processing = other.stop_processing;
        for (const auto &p : symbolTable)
        {
            this->symbolTable.emplace(p.first, p.second->clone());
        }
    }
    return *this;
}

void Context::addSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data)
{
    if (symbolTable.find(identifier) == symbolTable.end())
    {
        symbolTable.emplace(identifier, std::make_unique<VariableInfo>(dataType, data));
    }
    else
    {
        throw "variable already decleared, multiple definitions not allowed";
    }
}

void Context::addSymbol(const std::string &identifier, const typeInfo &dataType, const std::vector<std::pair<std::string, typeInfo>> &parameterList, BlockNode *const &functionBlockNode)
{
    symbolTable.emplace(identifier, std::make_unique<FunctionInfo>(dataType, parameterList, functionBlockNode));
}

void Context::addClass(const std::string &name, const classTypeInfo &info)
{
    classTable.emplace(name, std::make_unique<ClassInfo>(info));
}

void Context::addClass(const std::string &name, classTypeInfo &&info)
{
    classTable.emplace(name, std::make_unique<ClassInfo>(std::move(info)));
}

void Context::print() const
{
    std::cout << "----------- " << id << " ->" << scope_type << " -----------" << std::endl;

    for (auto &symbols : symbolTable)
    {
        std::cout << symbols.first << ":" << symbols.second->getType() << std::endl;
    }
    std::cout << std::endl;
}

// TODO: Find ways to piecewise emplace map with specified child class type
