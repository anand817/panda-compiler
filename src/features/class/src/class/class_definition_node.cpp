#include <class/nodes.hpp>
#include <functions/nodes.hpp>

ClassDefinitionNode::ClassDefinitionNode(const IdentifierNode &identifierNode, const DeclarationList &declarations)
    : identifierNode(identifierNode),
      declarations(declarations) {}

std::vector<std::string> ClassDefinitionNode::generateCode()
{
    return {};
}

bool ClassDefinitionNode::analyze()
{
    return true;
}

void ClassDefinitionNode::run()
{
    ClassTypeInfo classType(identifierNode.name);
    for (auto &declaration : declarations)
    {
        FunctionDeclarationNode *function = dynamic_cast<FunctionDeclarationNode *>(declaration);
        if (function != nullptr)
        {
            // i.e it is a function declaration node
            std::vector<std::pair<std::string, typeInfo>> parameterList;
            for (auto parameter : function->variableList)
            {
                parameterList.emplace_back(parameter.identifierNode.name, parameter.typeNode.type);
            }
            classType.addFunction(function->identifierNode.name, function->typeNode.type, function->functionBlockNode, parameterList);
        }
        else
        {
            // it is a variable declaration node
            classType.addProperty(declaration->identifierNode.name, declaration->typeNode.type);
        }
    }
    ContextHandler::addClass(identifierNode.name, std::move(classType));
}

void ClassDefinitionNode::print(std::string prefix)
{
    std::cout << prefix << "class definition node" << std::endl;
    prefix += "\t-> ";
    identifierNode.print(prefix);
    for (auto declaration : declarations)
    {
        declaration->print(prefix);
    }
}