#ifndef BASE_NODES_H
#define BASE_NODES_H

#include <vector>
#include <string>
#include <utils/nodes.hpp>

class Node
{
public:
    virtual std::vector<std::string> generateCode() = 0;
    virtual bool analyze() = 0;
    virtual void run() = 0;
};

class StatementNode : public Node
{
public:
    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
};

typedef std::vector<StatementNode *> StatementList;

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

    virtual ~BlockNode();
};

// abstract class for declaration
class DeclarationNode : public StatementNode
{
protected:
    TypeNode *typeNode;
    IdentifierNode *identifierNode;

public:
    DeclarationNode(TypeNode *const &type, IdentifierNode *const &identifier);

    virtual ~DeclarationNode();
};

#endif // BASE_NODES_H
