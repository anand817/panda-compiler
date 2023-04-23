#include <conditionals/nodes.hpp>
#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>

IfNode::IfNode(ExpressionNode *const &condition, BlockNode *const &ifBody)
    : conditional_expression(condition),
      ifBody(ifBody),
      elseBody(nullptr) {}

IfNode::IfNode(ExpressionNode *const &condition, BlockNode *const &ifBody, BlockNode *const &elseBody)
    : conditional_expression(condition),
      ifBody(ifBody),
      elseBody(elseBody) {}

IfNode::IfNode(const IfNode &other)
    : conditional_expression(other.conditional_expression),
      ifBody(other.ifBody),
      elseBody(other.elseBody) {}

IfNode::IfNode(IfNode &&other)
    : conditional_expression(std::move(other.conditional_expression)),
      ifBody(std::move(other.ifBody)),
      elseBody(std::move(other.elseBody)) {}

IfNode &IfNode::operator=(const IfNode &other)
{
    if (this != &other)
    {
        conditional_expression = other.conditional_expression;
        ifBody = other.ifBody;
        elseBody = other.elseBody;
    }
    return *this;
}
IfNode &IfNode::operator=(IfNode &&other)
{
    if (this != &other)
    {
        conditional_expression = std::move(other.conditional_expression);
        ifBody = std::move(other.ifBody);
        elseBody = std::move(other.elseBody);
    }
    return *this;
}

std::vector<std::string> IfNode::generateCode()
{
    return {};
}

bool IfNode::analyze()
{
    return true;
}
void IfNode::run()
{
    conditional_expression->run();
    if (getTypeString(conditional_expression->valueNode.type) != BOOL_TYPE)
    {
        throw "condition in if statement should be a boolean";
    }
    ContextHandler::pushContext(SCOPE_TYPE::BRANCH_SCOPE, this);
    if (std::get<bool>(conditional_expression->valueNode.value))
    {
        ifBody->run(SCOPE_TYPE::BRANCH_SCOPE);
    }
    else
    {
        if (elseBody)
            elseBody->run(SCOPE_TYPE::BRANCH_SCOPE);
    }
    ContextHandler::popContext();
}

void IfNode::print(std::string prefix)
{
    std::cout << prefix << "If Node" << std::endl;
    prefix += "\t-> ";
    conditional_expression->print(prefix);
    ifBody->print(prefix);
    if (elseBody)
    {
        elseBody->print(prefix);
    }
}