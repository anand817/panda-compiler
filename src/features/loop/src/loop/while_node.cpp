#include <loop/nodes.hpp>
#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>

WhileNode::WhileNode(ExpressionNode *const &condition, BlockNode *const &body)
    : condition_expression(condition),
      body(body) {}

WhileNode::WhileNode(const WhileNode &other)
    : condition_expression(other.condition_expression),
      body(other.body) {}

WhileNode::WhileNode(WhileNode &&other)
    : condition_expression(std::move(other.condition_expression)),
      body(std::move(other.body)) {}

WhileNode &WhileNode::operator=(const WhileNode &other)
{
    if (this != &other)
    {
        condition_expression = other.condition_expression;
        body = other.body;
    }
    return *this;
}

WhileNode &WhileNode::operator=(WhileNode &&other)
{
    if (this != &other)
    {
        condition_expression = std::move(other.condition_expression);
        body = std::move(other.body);
    }
    return *this;
}

std::vector<std::string> WhileNode::generateCode()
{
    return {};
}

bool WhileNode::analyze()
{
    return true;
}

void WhileNode::run()
{
    ContextHandler::pushContext(SCOPE_TYPE::LOOP_SCOPE, this);
    if (condition_expression == nullptr)
        throw " condition in while loop can't be null";

    condition_expression->run();
    if (getTypeString(condition_expression->valueNode.type) != BOOL_TYPE)
    {
        throw "conditional expression should be boolean";
    }
    if (body == nullptr)
    {
        throw "body of for statement can't be null";
    }

    while (condition_expression == nullptr || std::get<bool>(condition_expression->valueNode.value))
    {
        body->run();
        if (condition_expression)
            condition_expression->run();
    }
    ContextHandler::popContext();
}

void WhileNode::print(std::string prefix)
{
    std::cout << prefix << "While Node" << std::endl;
    prefix += "\t-> ";
    if (condition_expression)
        condition_expression->print(prefix);
    if (body)
        body->print(prefix);
}

void WhileNode::assignBody(BlockNode *const &body)
{
    this->body = body;
}