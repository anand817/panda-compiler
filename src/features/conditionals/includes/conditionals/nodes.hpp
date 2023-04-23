#ifndef CONDITIONALS_NODES_H
#define CONDITIONALS_NODES_H

#include <base/nodes.hpp>

class IfNode : public StatementNode
{
public:
    ExpressionNode *conditional_expression;
    BlockNode *ifBody, *elseBody;

    IfNode(ExpressionNode *const &condition, BlockNode *const &ifBody);
    IfNode(ExpressionNode *const &condition, BlockNode *const &ifBody, BlockNode *const &elseBody);

    IfNode(const IfNode &other);
    IfNode(IfNode &&other);

    IfNode &operator=(const IfNode &other);
    IfNode &operator=(IfNode &&other);

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
};

#endif // CONDITIONALS_NODES_H