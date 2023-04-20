#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <vector>
#include <memory>
#include <context/object.hpp>

// abstrcat class
class SymbolInfo
{
protected:
    std::string dataType;

public:
    SymbolInfo(const std::string &dataType);
    SymbolInfo(std::string &&dataType);

    virtual std::string getType() = 0;
    virtual std::unique_ptr<SymbolInfo> clone() = 0;
};

// implementations
class VariableInfo : public SymbolInfo
{
protected:
    valueType valueContainer;

public:
    VariableInfo(const std::string &dataType, const valueType &data);
    VariableInfo(const std::string &dataType, valueType &&data);

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
protected:
    std::vector<std::string> parameters;

public:
    FunctionInfo(std::string dataType, std::vector<std::string> parameterList);
    FunctionInfo(FunctionInfo &&other);
    FunctionInfo(const FunctionInfo &other);

    virtual std::string getType();
    virtual std::unique_ptr<SymbolInfo> clone();

    // operator overloads
    FunctionInfo &operator=(FunctionInfo &&other);
    FunctionInfo &operator=(const FunctionInfo &other);
};

#endif // SYMBOL_TABLE_H