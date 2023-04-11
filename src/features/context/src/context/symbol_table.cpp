#include <symbol_table.hpp>

SymbolInfo::SymbolInfo(std::string dataType)
{
    this->dataType = dataType;
}

SymbolInfo::SymbolInfo(SymbolInfo &&other)
{
    dataType = std::move(other.dataType);
}

SymbolInfo &SymbolInfo::operator=(SymbolInfo &&other)
{
    if (this != &other)
    {
        dataType = std::move(other.dataType);
    }

    return *this;
}