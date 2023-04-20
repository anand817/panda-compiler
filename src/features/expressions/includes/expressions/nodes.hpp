#ifndef EXPRESSION_NODES_H
#define EXPRESSION_NODES_H

#include <base/nodes.hpp>
#include <context/object.hpp>

class ExpressionNode : public StatementNode
{
protected:
    ValueNode valueNode;

public:
    ExpressionNode(const ValueNode &valueNode);
    ExpressionNode(ValueNode &&valueNode);

    ExpressionNode(const ExpressionNode &other);
    ExpressionNode(ExpressionNode &&other);

    ExpressionNode &operator=(const ExpressionNode &other);
    ExpressionNode &operator=(ExpressionNode &&other);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
};

#endif // EXPRESSION_NODES_H