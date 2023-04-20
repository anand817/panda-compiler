#ifndef BASE_NODES_H
#define BASE_NODES_H

#include <vector>
#include <string>
#include <utils/nodes.hpp>
#include <iostream>
#include <context/context_handler.hpp>

class Node
{
public:
    virtual std::vector<std::string> generateCode() = 0;
    virtual bool analyze() = 0;
    virtual void run() = 0;
    virtual void print(std::string prefix) = 0;
};

class StatementNode : public Node
{
public:
    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
};

typedef std::vector<StatementNode *> StatementList;
// pointers required to support runtime polymorphism

class BlockNode : public StatementNode
{
protected:
    StatementList statements;

public:
    BlockNode();
    BlockNode(const StatementList &statementList);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);

    virtual ~BlockNode();
};

// abstract class for declaration
class DeclarationNode : public StatementNode
{
protected:
    TypeNode typeNode;
    IdentifierNode identifierNode;

public:
    DeclarationNode(const TypeNode &type, const IdentifierNode &identifier);
};

#endif // BASE_NODES_H
