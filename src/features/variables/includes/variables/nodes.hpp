#ifndef VARIABLE_NODES_H
#define VARIABLE_NODES_H

#include <base/nodes.hpp>
#include <context/object.hpp>
#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>
#include <context/class_table.hpp>

class VariableDeclarationNode : public DeclarationNode
{
public:
    VariableDeclarationNode(const TypeNode &type, const IdentifierNode &identifier);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
};

class VariableDefinitionNode : public VariableDeclarationNode
{
public:
    ExpressionNode *expressionNode; // needed pointer for polymorphism

public:
    VariableDefinitionNode(const TypeNode &type, const IdentifierNode &identifiery, ExpressionNode *const &expressionNode);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);

    ~VariableDefinitionNode();
};

class ObjectDeclarationNode : public DeclarationNode
{
public:
    ObjectDeclarationNode(const std::string &typeName, const IdentifierNode &identifier);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
};
#endif // VARIABLE_NODES_H