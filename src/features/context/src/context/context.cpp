#include <context/context.hpp>
#include <iostream>

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

void Context::updateSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data)
{
    if (symbolTable.find(identifier) == symbolTable.end())
    {
        symbolTable.emplace(identifier, std::make_unique<VariableInfo>(dataType, data));
    }
    else
    {
        std::unique_ptr<SymbolInfo> &symbolInfo = symbolTable[identifier];
        if (getTypeString(symbolInfo->dataType) != getTypeString(dataType))
        {
            throw "unmatching type";
        }

        VariableInfo *variableInfo = dynamic_cast<VariableInfo *>(symbolInfo.get());
        if (variableInfo)
        {
            throw "not a variable";
        }

        variableInfo->valueContainer = data;
    }
}

void Context::addSymbol(const std::string &identifier, const typeInfo &dataType, const std::vector<std::string> &parameterList)
{
    symbolTable.emplace(identifier, std::make_unique<FunctionInfo>(dataType, parameterList));
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
    std::cout << "----------- " << id << " -----------" << std::endl;

    for (auto &symbols : symbolTable)
    {
        std::cout << symbols.first << ":" << symbols.second->getType() << std::endl;
    }
    std::cout << std::endl;
}

// TODO: Find ways to piecewise emplace map with specified child class type
