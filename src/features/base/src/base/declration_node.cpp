#include <base/nodes.hpp>

DeclarationNode::DeclarationNode(TypeNode *const &type, IdentifierNode *const &identifier)
{
    *(this->typeNode) = *type;             // copy type
    *(this->identifierNode) = *identifier; // copy identifier
}

DeclarationNode::~DeclarationNode()
{
    if (typeNode)
        delete typeNode;
    if (identifierNode)
        delete identifierNode;
}