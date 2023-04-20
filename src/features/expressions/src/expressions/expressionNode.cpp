#include <expressions/nodes.hpp>

ExpressionNode::ExpressionNode(const ValueNode &valueNode) : valueNode(valueNode) {}

ExpressionNode::ExpressionNode(ValueNode &&valueNode) : valueNode(std::move(valueNode)) {}

ExpressionNode::ExpressionNode(const ExpressionNode &other) : valueNode(other.valueNode) {}

ExpressionNode::ExpressionNode(ExpressionNode &&other) : valueNode(std::move(other.valueNode)) {}

ExpressionNode &ExpressionNode::operator=(const ExpressionNode &other)
{
    if (this != &other)
    {
        valueNode = other.valueNode;
    }
    return *this;
}

ExpressionNode &ExpressionNode::operator=(ExpressionNode &&other)
{
    if (this != &other)
    {
        valueNode = std::move(other.valueNode);
    }
    return *this;
}

std::vector<std::string> ExpressionNode::generateCode()
{
    return {};
}

bool ExpressionNode::analyze()
{
    return true;
}

void ExpressionNode::run() {}
