#include <variables/nodes.hpp>

VariableDefinitionNode::VariableDefinitionNode(const TypeNode &type, const IdentifierNode &identifier, ExpressionNode *const &expressionNode) : VariableDeclarationNode(type, identifier), expressionNode(expressionNode) {}

std::vector<std::string> VariableDefinitionNode::generateCode()
{
    return {};
}

bool VariableDefinitionNode::analyze()
{
    return true;
}

void VariableDefinitionNode::run() {}

VariableDefinitionNode::~VariableDefinitionNode()
{
    if (expressionNode)
    {
        delete expressionNode;
    }
}