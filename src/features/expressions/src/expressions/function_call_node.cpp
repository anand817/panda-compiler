#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>

FunctionCallNode::FunctionCallNode(const IdentifierNode &identifierNode, const ArgumentList &argumentList)
    : IdentifierExpressionNode(identifierNode),
      argumentList(argumentList) {}

FunctionCallNode::FunctionCallNode(const FunctionCallNode &other)
    : IdentifierExpressionNode(other),
      argumentList(other.argumentList) {}

FunctionCallNode::FunctionCallNode(FunctionCallNode &&other)
    : IdentifierExpressionNode(std::move(other)),
      argumentList(std::move(argumentList)) {}

FunctionCallNode &FunctionCallNode::operator=(const FunctionCallNode &other)
{
    if (this != &other)
    {
        IdentifierExpressionNode::operator=(other);
        this->argumentList = argumentList;
    }

    return *this;
}

FunctionCallNode &FunctionCallNode::operator=(FunctionCallNode &&other)
{
    if (this != &other)
    {
        IdentifierExpressionNode::operator=(std::move(other));
        this->argumentList = std::move(other.argumentList);
    }

    return *this;
}

ExpressionNode *FunctionCallNode::clone()
{
    return new FunctionCallNode(*this);
}

std::vector<std::string> FunctionCallNode::generateCode()
{
    return {};
}

bool FunctionCallNode::analyze()
{
    return true;
}

void FunctionCallNode::run()
{
    auto &symbolInfo = ContextHandler::findSymbol(identifierNode.name);
    if (symbolInfo == nullptr)
    {
        throw "identifier " + identifierNode.name + " not found";
    }

    FunctionInfo *info = dynamic_cast<FunctionInfo *>(symbolInfo.get());
    if (!info)
    {
        throw identifierNode.name + " is not a function ( check if its a variable )";
    }

    if (!info->functionBlockNode)
    {
        throw "function definition not found";
    }
    ContextHandler::pushContext(SCOPE_TYPE::FUNCTION_SCOPE);

    if (argumentList.size() != info->parameters.size())
    {
        throw "function argument length does not match";
    }

    for (auto i = 0; i < argumentList.size(); i++)
    {
        argumentList[i]->run(); // run the expressions in the argument list
        if (getTypeString(argumentList[i]->valueNode.type) != getTypeString(info->parameters[i].second))
        {
            throw "argument list doesnot match";
        }
        ContextHandler::addSymbol(info->parameters[i].first, info->parameters[i].second, argumentList[i]->valueNode.value);
    }

    info->functionBlockNode->run();
    ContextHandler::popContext();
    // this->valueNode = info->
}

void FunctionCallNode::print(std::string prefix)
{
    std::cout << prefix << "Function Call Node" << std::endl;
    prefix += "\t-> ";
    IdentifierExpressionNode::print(prefix);
    std::cout << prefix << "expressions: " << std::endl;
    for (auto expression : argumentList)
    {
        expression->print(prefix);
    }
}

bool FunctionCallNode::isLvalue()
{
    return false;
}
void FunctionCallNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    throw "function call is not an lvalue";
}