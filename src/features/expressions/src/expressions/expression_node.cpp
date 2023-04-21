#include <expressions/nodes.hpp>

ExpressionNode::ExpressionNode() {}

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

ExpressionNode *ExpressionNode::clone()
{
    return new ExpressionNode(*this);
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

bool ExpressionNode::isLvalue()
{
    // constant values are rvalue;
    return false;
}

void ExpressionNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    throw "constant expression is not an lvalue";
}

void ExpressionNode::print(std::string prefix)
{
    std::cout << prefix << "single valued Expression Node" << std::endl;
    prefix += "\t-> ";
    valueNode.print(prefix);
}
