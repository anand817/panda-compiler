#include <base/nodes.hpp>

DeclarationNode::DeclarationNode(const TypeNode &type, const IdentifierNode &identifier) : typeNode(type), identifierNode(identifier) {}

void DeclarationNode::print(std::string prefix)
{
    std::cout << prefix << "Declaration Node" << std::endl;
    prefix += "\t-> ";
    typeNode.print(prefix);
    identifierNode.print(prefix);
}