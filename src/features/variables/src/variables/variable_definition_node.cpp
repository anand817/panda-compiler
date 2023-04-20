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

void VariableDefinitionNode::print(std::string prefix)
{
    std::cout << prefix << "Variable Definition Node" << std::endl;
    prefix += "\t-> ";
    typeNode.print(prefix);
    identifierNode.print(prefix);
    expressionNode->print(prefix);
}

VariableDefinitionNode::~VariableDefinitionNode()
{
    if (expressionNode)
    {
        delete expressionNode;
    }
}