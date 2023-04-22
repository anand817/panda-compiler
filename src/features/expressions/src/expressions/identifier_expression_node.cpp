#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>

IdentifierExpressionNode::IdentifierExpressionNode(const IdentifierNode &identifierNode)
    : ExpressionNode(),
      identifierNode(identifierNode) {}

IdentifierExpressionNode::IdentifierExpressionNode(IdentifierNode &&identifierNode)
    : ExpressionNode(),
      identifierNode(std::move(identifierNode)) {}

IdentifierExpressionNode::IdentifierExpressionNode(const IdentifierExpressionNode &other)
    : ExpressionNode(other),
      identifierNode(other.identifierNode) {}

IdentifierExpressionNode::IdentifierExpressionNode(IdentifierExpressionNode &&other)
    : ExpressionNode(std::move(other)),
      identifierNode(std::move(other.identifierNode)) {}

IdentifierExpressionNode &IdentifierExpressionNode::operator=(const IdentifierExpressionNode &other)
{
    if (this != &other)
    {
        ExpressionNode::operator=(other);
        this->identifierNode = identifierNode;
    }
    return *this;
}

IdentifierExpressionNode &IdentifierExpressionNode::operator=(IdentifierExpressionNode &&other)
{
    if (this != &other)
    {
        ExpressionNode::operator=(std::move(other));
        this->identifierNode = std::move(other.identifierNode);
    }

    return *this;
}

IdentifierExpressionNode *IdentifierExpressionNode::clone()
{
    return new IdentifierExpressionNode(*this);
}

std::vector<std::string> IdentifierExpressionNode::generateCode()
{
    return {};
}
bool IdentifierExpressionNode::analyze()
{
    return true;
}
void IdentifierExpressionNode::run()
{
    auto &symbolInfo = ContextHandler::findSymbol(identifierNode.name);
    if (symbolInfo == nullptr)
    {
        throw "identifier " + identifierNode.name + " not found";
    }

    VariableInfo *info = dynamic_cast<VariableInfo *>(symbolInfo.get());
    if (!info)
    {
        throw identifierNode.name + " is not a variable ( check if its a function )";
    }

    this->valueNode.value = info->valueContainer;
    this->valueNode.type = info->dataType;
}

bool IdentifierExpressionNode::isLvalue()
{
    // identifier is an lvalue
    return true;
}

void IdentifierExpressionNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    ContextHandler::updateSymbol(identifierNode.name, dataType, data);
}

void IdentifierExpressionNode::print(std::string prefix)
{
    std::cout << prefix << "identifier Expression Node" << std::endl;
    prefix += "\t-> ";
    std::cout << prefix << identifierNode.name << std::endl;
    valueNode.print(prefix);
}
