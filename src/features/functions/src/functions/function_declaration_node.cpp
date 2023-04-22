#include <functions/nodes.hpp>

FunctionDeclarationNode::FunctionDeclarationNode(const TypeNode &typeNode, const IdentifierNode &identifierNode, const VariableList &variableList, BlockNode *const &functionBlockNode)
    : DeclarationNode(typeNode, identifierNode),
      variableList(variableList),
      functionBlockNode(functionBlockNode) {}

std::vector<std::string> FunctionDeclarationNode::generateCode()
{
    return {};
}

bool FunctionDeclarationNode::analyze()
{
    return false;
}

void FunctionDeclarationNode::run()
{
    std::vector<std::pair<std::string, typeInfo>> parameterList;
    for (auto parameter : variableList)
    {
        parameterList.emplace_back(parameter.identifierNode.name, parameter.typeNode.type);
    }
    ContextHandler::addSymbol(identifierNode.name, typeNode.type, parameterList, functionBlockNode);
}

void FunctionDeclarationNode::assignBody(BlockNode *const &functionBlockNode)
{
    this->functionBlockNode = functionBlockNode;
}

void FunctionDeclarationNode::print(std::string prefix)
{
    std::cout << prefix << "function declaration node" << std::endl;
    prefix += "\t-> ";
    DeclarationNode::print(prefix);
    for (auto variableNode : variableList)
    {
        variableNode.print(prefix);
    }
    if (functionBlockNode)
    {
        functionBlockNode->print(prefix);
    }
    else
    {
        std::cout << prefix << " function node is just declaration" << std::endl;
    }
}