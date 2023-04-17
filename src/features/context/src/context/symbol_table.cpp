#include <context/symbol_table.hpp>

SymbolInfo::SymbolInfo(std::string dataType)
{
    this->dataType = dataType;
}

SymbolInfo::SymbolInfo(SymbolInfo &&other)
{
    dataType = std::move(other.dataType);
}

SymbolInfo::SymbolInfo(const SymbolInfo &other)
{
    dataType = other.dataType;
}

SymbolInfo &SymbolInfo::operator=(SymbolInfo &&other)
{
    if (this != &other)
    {
        dataType = std::move(other.dataType);
    }

    return *this;
}

SymbolInfo &SymbolInfo::operator=(const SymbolInfo &other)
{
    if (this != &other)
    {
        dataType = other.dataType;
    }

    return *this;
}