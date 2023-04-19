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

void Context::addSymbol(const std::string &identifier, const std::string &dataType, const allType &data)
{
    symbolTable.emplace(identifier, std::make_unique<VariableInfo>(dataType, data));
}

void Context::addSymbol(const std::string &identifier, const std::string &dataType, const std::vector<std::string> &parameterList)
{
    symbolTable.emplace(identifier, std::make_unique<FunctionInfo>(dataType, parameterList));
}

void Context::addClass(const std::string &name, const std::map<std::string, std::unique_ptr<SymbolInfo>> &info)
{
    classTable.emplace(name, std::make_unique<ClassInfo>(info));
}

void Context::addClass(const std::string &name, std::map<std::string, std::unique_ptr<SymbolInfo>> &&info)
{
    classTable.emplace(name, std::make_unique<ClassInfo>(std::move(info)));
}

// TODO: Find ways to piecewise emplace map with specified child class type
