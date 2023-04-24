#ifndef EXPRESSION_NODES_H
#define EXPRESSION_NODES_H

#include <base/nodes.hpp>
#include <context/object.hpp>
#include <context/class_table.hpp>
#include <context/symbol_table.hpp>
#include <enums/operation_enum.hpp>

class ExpressionNode : public StatementNode
{
public:
    ValueNode valueNode;

public:
    // to instantiate empty valued expression when uninitiazed
    ExpressionNode();
    ExpressionNode(const ValueNode &valueNode);
    ExpressionNode(ValueNode &&valueNode);

    ExpressionNode(const ExpressionNode &other);
    ExpressionNode(ExpressionNode &&other);

    ExpressionNode &operator=(const ExpressionNode &other);
    ExpressionNode &operator=(ExpressionNode &&other);

    ExpressionNode *clone();

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

class IdentifierExpressionNode : public ExpressionNode
{
public:
    IdentifierNode identifierNode;

public:
    IdentifierExpressionNode(const IdentifierNode &identifierNode);
    IdentifierExpressionNode(IdentifierNode &&identifierNode);

    IdentifierExpressionNode(const IdentifierExpressionNode &other);
    IdentifierExpressionNode(IdentifierExpressionNode &&other);

    IdentifierExpressionNode &operator=(const IdentifierExpressionNode &other);
    IdentifierExpressionNode &operator=(IdentifierExpressionNode &&other);

    IdentifierExpressionNode *clone();

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

class UnaryExpressionNode : public ExpressionNode
{
public:
    ExpressionNode *expression;
    UNARY_OPERATOR operation;

public:
    UnaryExpressionNode(ExpressionNode *const &expression, UNARY_OPERATOR operation);

    UnaryExpressionNode(const UnaryExpressionNode &other);
    UnaryExpressionNode(UnaryExpressionNode &&other);

    UnaryExpressionNode &operator=(const UnaryExpressionNode &other);
    UnaryExpressionNode &operator=(UnaryExpressionNode &&other);

    ExpressionNode *clone();

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

class BinaryExpressionNode : public ExpressionNode
{
public:
    ExpressionNode *left_expression, *right_expression;
    BINARY_OPERATOR operation;

    BinaryExpressionNode(ExpressionNode *const &left_expression, ExpressionNode *const &right_expression, BINARY_OPERATOR operation);

    BinaryExpressionNode(const BinaryExpressionNode &other);
    BinaryExpressionNode(BinaryExpressionNode &&other);

    BinaryExpressionNode &operator=(const BinaryExpressionNode &other);
    BinaryExpressionNode &operator=(BinaryExpressionNode &&other);

    ExpressionNode *clone();

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

typedef std::vector<ExpressionNode *> ArgumentList;

class FunctionCallNode : public IdentifierExpressionNode
{
public:
    ArgumentList argumentList;
    TypeNode typeNode;

    FunctionCallNode(const IdentifierNode &identifierNode, const ArgumentList &argumentList);

    FunctionCallNode(const FunctionCallNode &other);
    FunctionCallNode(FunctionCallNode &&other);

    FunctionCallNode &operator=(const FunctionCallNode &other);
    FunctionCallNode &operator=(FunctionCallNode &&other);

    ExpressionNode *clone();

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

class PrintNode : public FunctionCallNode
{
public:
    PrintNode(const ArgumentList &argumentList);

    PrintNode(const PrintNode &other);
    PrintNode(PrintNode &&other);

    PrintNode &operator=(const PrintNode &other);
    PrintNode &operator=(PrintNode &&other);

    ExpressionNode *clone();

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

class InputNode : public FunctionCallNode
{
public:
    InputNode(const ArgumentList &argumentList);

    InputNode(const InputNode &other);
    InputNode(InputNode &&other);

    InputNode &operator=(const InputNode &other);
    InputNode &operator=(InputNode &&other);

    ExpressionNode *clone();

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

class ObjectVariableNode : public ExpressionNode
{
public:
    IdentifierNode objectIdentifier, parameterIdentifier;

    ObjectVariableNode(const IdentifierNode &objectIdentifier, const IdentifierNode &parameterIdentifier);

    ObjectVariableNode(const ObjectVariableNode &other);
    ObjectVariableNode(ObjectVariableNode &&other);

    ObjectVariableNode &operator=(const ObjectVariableNode &other);
    ObjectVariableNode &operator=(ObjectVariableNode &&other);

    ExpressionNode *clone();

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

class ObjectFunctionCallNode : public FunctionCallNode
{
public:
    IdentifierNode objectIdentifierNode;

    ObjectFunctionCallNode(const IdentifierNode &objectIdentifierNode, const IdentifierNode &functionParameterIdentifierNode, const ArgumentList &argumentList);

    ObjectFunctionCallNode(const ObjectFunctionCallNode &other);
    ObjectFunctionCallNode(const ObjectFunctionCallNode &&other);

    ObjectFunctionCallNode &operator=(const ObjectFunctionCallNode &other);
    ObjectFunctionCallNode &operator=(ObjectFunctionCallNode &&other);

    ExpressionNode *clone();

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
    virtual bool isLvalue();
    virtual void updateSymbol(const typeInfo &dataType, const valueType &data);
    virtual std::unique_ptr<SymbolInfo> &getSymbol();
};

#endif // EXPRESSION_NODES_H