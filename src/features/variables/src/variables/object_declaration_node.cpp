#include <variables/nodes.hpp>

ObjectDeclarationNode::ObjectDeclarationNode(const std::string &typeName, const IdentifierNode &identifier)
    : DeclarationNode(TypeNode(typeName), identifier) {}

std::vector<std::string> ObjectDeclarationNode::generateCode()
{
    return {};
}

bool ObjectDeclarationNode::analyze()
{
    return true;
}

void ObjectDeclarationNode::run()
{
    std::string className = std::get<std::string>(typeNode.type);
    auto &classInfo = ContextHandler::findClass(className);
    if (classInfo == nullptr)
    {
        throw "No class named " + className + " in current scope";
    }
    typeNode.type = classInfo->info;
    objectType value;
    value.className = className;
    // assign default values to the object
    for (auto &p : classInfo->info.propertyInfo)
    {
        value.parameters[p.first] = getDefaultValue(getTypeString(p.second));
    }
    ContextHandler::addSymbol(identifierNode.name, typeNode.type, std::make_shared<objectType>(value));
}

void ObjectDeclarationNode::print(std::string prefix)
{
    std::cout << prefix << "Object declaration node" << std::endl;
    prefix += "\t-> ";
    DeclarationNode::print(prefix);
}