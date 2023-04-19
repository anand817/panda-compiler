#include <base/nodes.hpp>

DeclarationNode::DeclarationNode(const TypeNode &type, const IdentifierNode &identifier) : typeNode(type), identifierNode(identifier) {}