#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>

ObjectFunctionCallNode::ObjectFunctionCallNode(const IdentifierNode &objectIdentifierNode, const IdentifierNode &functionParameterIdentifierNode, const ArgumentList &argumentList)
    : FunctionCallNode(functionParameterIdentifierNode, argumentList),
      objectIdentifierNode(objectIdentifierNode) {}

ObjectFunctionCallNode::ObjectFunctionCallNode(const ObjectFunctionCallNode &other)
    : FunctionCallNode(other),
      objectIdentifierNode(other.objectIdentifierNode) {}

ObjectFunctionCallNode::ObjectFunctionCallNode(const ObjectFunctionCallNode &&other)
    : FunctionCallNode(std::move(other)),
      objectIdentifierNode(std::move(other.objectIdentifierNode)) {}

ObjectFunctionCallNode &ObjectFunctionCallNode::operator=(const ObjectFunctionCallNode &other)
{
    if (this != &other)
    {
        FunctionCallNode::operator=(other);
        this->objectIdentifierNode = objectIdentifierNode;
    }
    return *this;
}

ObjectFunctionCallNode &ObjectFunctionCallNode::operator=(ObjectFunctionCallNode &&other)
{
    if (this != &other)
    {
        FunctionCallNode::operator=(std::move(other));
        this->objectIdentifierNode = std::move(other.objectIdentifierNode);
    }
    return *this;
}

ExpressionNode *ObjectFunctionCallNode::clone()
{
    return new ObjectFunctionCallNode(*this);
}

std::vector<std::string> ObjectFunctionCallNode::generateCode()
{
    return {};
}

bool ObjectFunctionCallNode::analyze()
{
    return false;
}

void ObjectFunctionCallNode::run()
{
    auto &symbolInfo = ContextHandler::findSymbol(objectIdentifierNode.name);
    if (symbolInfo == nullptr)
    {
        throw "undefiend object " + objectIdentifierNode.name;
    }
    VariableInfo *variableInfo = dynamic_cast<VariableInfo *>(symbolInfo.get());
    if (variableInfo == nullptr || !(std::holds_alternative<std::shared_ptr<objectType>>(variableInfo->valueContainer)))
    {
        throw "identifier " + objectIdentifierNode.name + " is not an object";
    }
    std::shared_ptr<objectType> &objectInfo = std::get<std::shared_ptr<objectType>>(variableInfo->valueContainer);
    if (objectInfo->info.functionInfo.find(identifierNode.name) == objectInfo->info.functionInfo.end())
    {
        throw "function " + identifierNode.name + " is not defined for this object";
    }
    auto &functionInfo = objectInfo->info.functionInfo.at(identifierNode.name);
    typeNode = TypeNode(functionInfo.returnType);
    ContextHandler::pushContext(SCOPE_TYPE::FUNCTION_SCOPE, this);
    if (argumentList.size() != functionInfo.parameters.size())
    {
        throw "function argument length does not match";
    }

    for (auto i = 0; i < argumentList.size(); i++)
    {
        argumentList[i]->run(); // run the expressions in the argument list
        if (getTypeString(argumentList[i]->valueNode.type) != getTypeString(functionInfo.parameters[i].second))
        {
            throw "argument list doesnot match";
        }
        ContextHandler::addSymbol(functionInfo.parameters[i].first, functionInfo.parameters[i].second, argumentList[i]->valueNode.value);
    }

    for (auto &parameterPair : objectInfo->info.propertyInfo)
    {
        ContextHandler::addSymbol(parameterPair.first, parameterPair.second, objectInfo->parameters[parameterPair.first]);
    }

    functionInfo.functionNode->run(SCOPE_TYPE::FUNCTION_SCOPE);

    objectType value(*objectInfo.get());

    for (auto &parameterPair : objectInfo->info.propertyInfo)
    {
        auto &objectSymbolInfo = ContextHandler::findSymbol(parameterPair.first);
        if (objectSymbolInfo == nullptr)
        {
            throw "undefined variable of object " + parameterPair.first;
        }
        VariableInfo *variableInfo = dynamic_cast<VariableInfo *>(objectSymbolInfo.get());
        if (variableInfo == nullptr || variableInfo->getType() != getTypeString(parameterPair.second))
        {
            throw "identifier " + parameterPair.first + " type is not same as object atrribute";
        }
        value.parameters[parameterPair.first] = variableInfo->valueContainer;
    }
    ContextHandler::popContext();
    ContextHandler::updateSymbol(objectIdentifierNode.name, objectInfo->info, std::make_shared<objectType>(value));
}

void ObjectFunctionCallNode::print(std::string prefix)
{
    std::cout << prefix << "object function call node" << std::endl;
    FunctionCallNode::print(prefix);
}

bool ObjectFunctionCallNode::isLvalue()
{
    return false;
}

void ObjectFunctionCallNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    throw "function call is not an lvalue";
}

std::unique_ptr<SymbolInfo> &ObjectFunctionCallNode::getSymbol()
{
    throw "function call is not an lvalue";
}