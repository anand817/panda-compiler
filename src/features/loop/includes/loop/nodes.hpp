#ifndef LOOP_NODES_H
#define LOOP_NODES_H
#include <base/nodes.hpp>

class ForNode : public StatementNode
{
public:
    StatementNode *initialize_statement;
    ExpressionNode *condition_expression;
    ExpressionNode *update_expression;
    BlockNode *body;

    ForNode(StatementNode *const &initialzer, ExpressionNode *const &condition, ExpressionNode *const &updation, BlockNode *const &body);

    ForNode(const ForNode &other);
    ForNode(ForNode &&other);

    ForNode &operator=(const ForNode &other);
    ForNode &operator=(ForNode &&other);

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);

    void assignBody(BlockNode *const &body);
};

class WhileNode : public StatementNode
{
public:
    ExpressionNode *condition_expression;
    BlockNode *body;

    WhileNode(ExpressionNode *const &condition, BlockNode *const &body);

    WhileNode(const WhileNode &other);
    WhileNode(WhileNode &&other);

    WhileNode &operator=(const WhileNode &other);
    WhileNode &operator=(WhileNode &&other);

    std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);

    void assignBody(BlockNode *const &body);
};

#endif // LOOP_NODES_H