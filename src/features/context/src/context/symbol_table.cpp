#include <context/symbol_table.hpp>

// VariableInfo

VariableInfo::VariableInfo(std::string dataType, const allType &data) : value(data)
{
    this->dataType = dataType;
}

VariableInfo::VariableInfo(std::string dataType, allType &&data) : value(std::move(data))
{
    this->dataType = dataType;
}

VariableInfo::VariableInfo(std::string dataType, const std::map<std::string, std::unique_ptr<SymbolInfo>> &properties) : value(properties)
{
    this->dataType = dataType;
}

VariableInfo::VariableInfo(std::string dataType, std::map<std::string, std::unique_ptr<SymbolInfo>> &&properties) : value(std::move(properties))
{
    this->dataType = dataType;
}

VariableInfo::VariableInfo(VariableInfo &&other) : value(std::move(other.value))
{
    dataType = std::move(other.dataType);
}

VariableInfo::VariableInfo(const VariableInfo &other) : value(other.value)
{
    dataType = other.dataType;
}

VariableInfo &VariableInfo::operator=(VariableInfo &&other)
{
    if (this != &other)
    {
        dataType = std::move(other.dataType);
        value = std::move(other.value);
    }

    return *this;
}

VariableInfo &VariableInfo::operator=(const VariableInfo &other)
{
    if (this != &other)
    {
        dataType = other.dataType;
        value = other.value;
    }

    return *this;
}

std::string VariableInfo::getType()
{
    return dataType;
}

std::unique_ptr<SymbolInfo> VariableInfo::clone()
{
    return std::make_unique<VariableInfo>(*this);
}

// FunctionInfo

FunctionInfo::FunctionInfo(std::string dataType, std::vector<std::string> parameterList)
{
    this->dataType = dataType;
    this->parameters = parameterList;
}

FunctionInfo::FunctionInfo(FunctionInfo &&other)
{
    dataType = std::move(other.dataType);
    this->parameters = std::move(other.parameters);
}

FunctionInfo::FunctionInfo(const FunctionInfo &other)
{
    dataType = other.dataType;
    parameters = other.parameters;
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
    return dataType;
}

std::unique_ptr<SymbolInfo> FunctionInfo::clone()
{
    return std::make_unique<FunctionInfo>(*this);
}