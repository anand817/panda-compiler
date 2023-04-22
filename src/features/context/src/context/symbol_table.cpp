#include <context/symbol_table.hpp>

// SymbolInfo

SymbolInfo::SymbolInfo(const typeInfo &dataType) : dataType(dataType) {}
SymbolInfo::SymbolInfo(typeInfo &&dataType) : dataType(std::move(dataType)) {}

// VariableInfo

VariableInfo::VariableInfo(const typeInfo &dataType, const valueType &data) : SymbolInfo(dataType), valueContainer(data) {}
VariableInfo::VariableInfo(typeInfo &&dataType, valueType &&data) : SymbolInfo(dataType), valueContainer(std::move(data)) {}

VariableInfo::VariableInfo(VariableInfo &&other) : SymbolInfo(std::move(other.dataType)), valueContainer(std::move(other.valueContainer)) {}
VariableInfo::VariableInfo(const VariableInfo &other) : SymbolInfo(other.dataType), valueContainer(other.valueContainer) {}

VariableInfo &VariableInfo::operator=(VariableInfo &&other)
{
    if (this != &other)
    {
        dataType = std::move(other.dataType);
        valueContainer = std::move(other.valueContainer);
    }

    return *this;
}

VariableInfo &VariableInfo::operator=(const VariableInfo &other)
{
    if (this != &other)
    {
        dataType = other.dataType;
        valueContainer = other.valueContainer;
    }

    return *this;
}

std::string VariableInfo::getType()
{
    return getTypeString(dataType);
}

std::unique_ptr<SymbolInfo> VariableInfo::clone()
{
    return std::make_unique<VariableInfo>(*this);
}

// FunctionInfo

FunctionInfo::FunctionInfo(const typeInfo &dataType, const std::vector<std::pair<std::string, typeInfo>> &parameterList, BlockNode *const &functionBlockNode) : SymbolInfo(dataType), parameters(parameterList), functionBlockNode(functionBlockNode) {}

FunctionInfo::FunctionInfo(FunctionInfo &&other) : SymbolInfo(std::move(other.dataType)), parameters(std::move(other.parameters)), functionBlockNode(std::move(other.functionBlockNode)) {}

FunctionInfo::FunctionInfo(const FunctionInfo &other) : SymbolInfo(other.dataType), parameters(other.parameters)
{
    *(this->functionBlockNode) = *functionBlockNode; // copy function block node
}

FunctionInfo &FunctionInfo::operator=(FunctionInfo &&other)
{
    if (this != &other)
    {
        dataType = std::move(other.dataType);
        parameters = std::move(other.parameters);
    }

    return *this;
}

FunctionInfo &FunctionInfo::operator=(const FunctionInfo &other)
{
    if (this != &other)
    {
        dataType = other.dataType;
        parameters = other.parameters;
    }

    return *this;
}

std::string FunctionInfo::getType()
{
    std::string dtype = getTypeString(dataType);
    dtype += " ( ";
    for (auto &p : parameters)
    {
        dtype += getTypeString(p.second);
        dtype += ", ";
    }
    dtype += " ) ";
    return dtype;
}

std::unique_ptr<SymbolInfo> FunctionInfo::clone()
{
    return std::make_unique<FunctionInfo>(*this);
}