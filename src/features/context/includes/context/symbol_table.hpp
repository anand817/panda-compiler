#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>

class SymbolInfo
{
private:
    std::string dataType;

public:
    // constructors
    SymbolInfo(std::string dataType);
    SymbolInfo(SymbolInfo &&other);

    // operator overloads
    SymbolInfo &operator=(SymbolInfo &&other);
};

#endif // SYMBOL_TABLE_H