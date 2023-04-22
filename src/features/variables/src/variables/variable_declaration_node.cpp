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

void VariableDeclarationNode::run()
{
    ContextHandler::addSymbol(identifierNode.name, typeNode.type, getDefaultValue(getTypeString(typeNode.type)));
}

void VariableDeclarationNode::print(std::string prefix)
{
    std::cout << prefix << "Variable declaration node" << std::endl;
    prefix += "\t-> ";
    DeclarationNode::print(prefix);
}