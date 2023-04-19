#include <variables/nodes.hpp>
VariableDefinitionNode::VariableDefinitionNode(TypeNode *const &type, IdentifierNode *const &identifier) : VariableDeclarationNode(type, identifier) {}

std::vector<std::string> VariableDefinitionNode::generateCode() {}

bool VariableDefinitionNode::analyze() {}

void VariableDefinitionNode::run() {}