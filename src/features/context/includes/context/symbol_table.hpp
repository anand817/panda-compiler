#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <vector>
#include <memory>
#include <context/object.hpp>
#include <context/class_table.hpp>

// abstrcat class
class SymbolInfo
{
public:
    typeInfo dataType;

public:
    SymbolInfo(const typeInfo &dataType);
    SymbolInfo(typeInfo &&dataType);

    virtual std::string getType() = 0;
    virtual std::unique_ptr<SymbolInfo> clone() = 0;
};

// implementations
class VariableInfo : public SymbolInfo
{
public:
    valueType valueContainer;

public:
    VariableInfo(const typeInfo &dataType, const valueType &data);
    VariableInfo(typeInfo &&dataType, valueType &&data);

    VariableInfo(VariableInfo &&other);
    VariableInfo(const VariableInfo &other);

    virtual std::string getType();
    virtual std::unique_ptr<SymbolInfo> clone();

    // operator overloads
    VariableInfo &operator=(VariableInfo &&other);
    VariableInfo &operator=(const VariableInfo &other);
};

class FunctionInfo : public SymbolInfo
{
public:
    std::vector<std::string> parameters;

public:
    FunctionInfo(const typeInfo &dataType, std::vector<std::string> parameterList);
    FunctionInfo(FunctionInfo &&other);
    FunctionInfo(const FunctionInfo &other);

    virtual std::string getType();
    virtual std::unique_ptr<SymbolInfo> clone();

    // operator overloads
    FunctionInfo &operator=(FunctionInfo &&other);
    FunctionInfo &operator=(const FunctionInfo &other);
};

#endif // SYMBOL_TABLE_H