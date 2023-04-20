#include <variables/nodes.hpp>

VariableDeclarationNode::VariableDeclarationNode(const TypeNode &type, const IdentifierNode &identifier) : DeclarationNode(type, identifier) {}

std::vector<std::string> VariableDeclarationNode::generateCode()
{
    return {};
}

bool VariableDeclarationNode::analyze()
{
    return true;
}

void VariableDeclarationNode::run() {}