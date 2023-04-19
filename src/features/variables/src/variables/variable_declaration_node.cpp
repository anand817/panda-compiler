#include <variables/nodes.hpp>

VariableDeclarationNode::VariableDeclarationNode(const TypeNode &type, const IdentifierNode &identifier) : DeclarationNode(type, identifier) {}

std::vector<std::string> VariableDeclarationNode::generateCode() {}

bool VariableDeclarationNode::analyze() {}

void VariableDeclarationNode::run() {}