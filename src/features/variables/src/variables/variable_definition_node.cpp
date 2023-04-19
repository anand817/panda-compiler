#include <variables/nodes.hpp>
VariableDefinitionNode::VariableDefinitionNode(const TypeNode &type, const IdentifierNode &identifier) : VariableDeclarationNode(type, identifier) {}

std::vector<std::string> VariableDefinitionNode::generateCode() {}

bool VariableDefinitionNode::analyze() {}

void VariableDefinitionNode::run() {}