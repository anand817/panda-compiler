#include <utils/nodes.hpp>

// all constructor definitions

TypeNode::TypeNode(const std::string &type) : type(type) {}

TokenNode::TokenNode(const std::string &value) : value(value) {}

IdentifierNode::IdentifierNode(const std::string &name) : name(name) {}

ValueNode::ValueNode(const std::string &type, const std::string &value) : type(type), value(value) {}