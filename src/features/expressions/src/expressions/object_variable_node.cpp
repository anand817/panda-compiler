#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>

ObjectVariableNode::ObjectVariableNode(const IdentifierNode &objectIdentifier, const IdentifierNode &parameterIdentifier)
    : objectIdentifier(objectIdentifier),
      parameterIdentifier(parameterIdentifier) {}

ObjectVariableNode::ObjectVariableNode(const ObjectVariableNode &other)
    : objectIdentifier(other.objectIdentifier),
      parameterIdentifier(other.parameterIdentifier) {}

ObjectVariableNode::ObjectVariableNode(ObjectVariableNode &&other)
    : objectIdentifier(std::move(other.objectIdentifier)),
      parameterIdentifier(std::move(other.parameterIdentifier)) {}

ObjectVariableNode &ObjectVariableNode::operator=(const ObjectVariableNode &other)
{
    if (this != &other)
    {
        objectIdentifier = other.objectIdentifier;
        parameterIdentifier = other.parameterIdentifier;
    }
    return *this;
}

ObjectVariableNode &ObjectVariableNode::operator=(ObjectVariableNode &&other)
{
    if (this != &other)
    {
        objectIdentifier = std::move(other.objectIdentifier);
        parameterIdentifier = std::move(other.parameterIdentifier);
    }
    return *this;
}

ExpressionNode *ObjectVariableNode::clone()
{
    return new ObjectVariableNode(*this);
}

std::vector<std::string> ObjectVariableNode::generateCode()
{
    return {};
}

bool ObjectVariableNode::analyze()
{
    return true;
}

void ObjectVariableNode::run()
{
    auto &symbolInfo = ContextHandler::findSymbol(objectIdentifier.name);
    if (symbolInfo == nullptr)
    {
        throw "undefiend object " + objectIdentifier.name;
    }
    VariableInfo *variableInfo = dynamic_cast<VariableInfo *>(symbolInfo.get());
    if (variableInfo == nullptr || !(std::holds_alternative<std::shared_ptr<objectType>>(variableInfo->valueContainer)))
    {
        throw "identifier " + objectIdentifier.name + " is not an object";
    }
    std::shared_ptr<objectType> &objectInfo = std::get<std::shared_ptr<objectType>>(variableInfo->valueContainer);
    if (objectInfo->parameters.find(parameterIdentifier.name) == objectInfo->parameters.end())
    {
        throw "identifier " + parameterIdentifier.name + " is not a parameter in the object";
    }
    this->valueNode.assignValue(objectInfo->parameters[parameterIdentifier.name]);
    // assigns both type and value
}

void ObjectVariableNode::print(std::string prefix)
{
    std::cout << prefix << "object variable Node" << std::endl;
    prefix += "\t-> ";
    objectIdentifier.print(prefix);
    parameterIdentifier.print(prefix);
}

bool ObjectVariableNode::isLvalue()
{
    return true;
}

void ObjectVariableNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    ContextHandler::updateObject(objectIdentifier.name, parameterIdentifier.name, this->valueNode.type, dataType, data);
}

std::unique_ptr<SymbolInfo> &ObjectVariableNode::getSymbol()
{
    throw "can't take input this way";
}
