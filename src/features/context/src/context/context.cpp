#include <context/context.hpp>

Context::Context(int id, const std::map<std::string, std::unique_ptr<SymbolInfo>> &symbolTable)
{
    this->id = id;
    for (const auto &p : symbolTable)
    {
        this->symbolTable.emplace(p.first, p.second->clone());
    }
}

Context::Context(int id, std::map<std::string, std::unique_ptr<SymbolInfo>> &&symbolTable)
{
    this->id = id;
    this->symbolTable = std::move(symbolTable);
}

Context::Context(int id)
{
    this->id = id;
    this->symbolTable.clear();
}

Context::Context(Context &&other)
{
    id = other.id;
    symbolTable = std::move(other.symbolTable);
}

Context::Context(const Context &other)
{
    id = other.id;
    for (const auto &p : symbolTable)
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
    }

    return *this;
}

Context &Context::operator=(const Context &other)
{
    if (this != &other)
    {
        id = other.id;
        for (const auto &p : symbolTable)
        {
            this->symbolTable.emplace(p.first, p.second->clone());
        }
    }
    return *this;
}

void Context::addSymbol(std::string identifier, std::string dataType, allType &data)
{
    symbolTable.emplace(identifier, std::make_unique<VariableInfo>(dataType, data));
}

void Context::addSymbol(std::string identifier, std::string dataType, std::vector<std::string> &parameterList)
{
    symbolTable.emplace(identifier, std::make_unique<FunctionInfo>(dataType, parameterList));
}

// TODO: Find ways to piecewise emplace map with specified child class type
