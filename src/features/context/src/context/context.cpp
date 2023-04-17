#include <context/context.hpp>

Context::Context(int id, std::map<std::string, SymbolInfo> symbolTable)
{
    this->id = id;
    this->symbolTable = symbolTable;
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
    symbolTable = other.symbolTable;
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
        symbolTable = other.symbolTable;
    }
    return *this;
}

void Context::addSymbol(std::string identifier, std::string dataType)
{
    symbolTable.emplace(std::piecewise_construct, std::make_tuple(identifier), std::make_tuple(dataType));
}