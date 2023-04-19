#include <variables/nodes.hpp>

VariableDeclarationNode::VariableDeclarationNode(TypeNode *const &type, IdentifierNode *const &identifier) : DeclarationNode(type, identifier) {}

std::vector<std::string> VariableDeclarationNode::generateCode()
{
}

bool VariableDeclarationNode::analyze()
{
}

void VariableDeclarationNode::run()
{
}