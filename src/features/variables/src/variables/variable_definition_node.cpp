#include <variables/nodes.hpp>

VariableDefinitionNode::VariableDefinitionNode(const TypeNode &type, const IdentifierNode &identifier, ExpressionNode *const &expressionNode) : VariableDeclarationNode(type, identifier), expressionNode(expressionNode) {}

std::vector<std::string> VariableDefinitionNode::generateCode()
{
    return {};
}

bool VariableDefinitionNode::analyze()
{
    return true;
}

void VariableDefinitionNode::run()
{
    overload type_overload{
        [](std::string &variableType, std::string expressionType)
        {
            if (variableType != expressionType)
            {
                throw("mismatched types " + variableType + " and " + expressionType);
            }
        },
        [](ClassTypeInfo &variableType, ClassTypeInfo &expressionType)
        {
            if (variableType.className != expressionType.className)
            {
                throw "mismatched class types";
            }
        },
        [](auto &variableType, auto &expressionType)
        {
            throw "mismatched auto types";
        }};

    expressionNode->run();
    std::visit(type_overload, typeNode.type, expressionNode->valueNode.type);
    ContextHandler::addSymbol(identifierNode.name, typeNode.type, expressionNode->valueNode.value);
}

void VariableDefinitionNode::print(std::string prefix)
{
    std::cout << prefix << "Variable Definition Node" << std::endl;
    prefix += "\t-> ";
    typeNode.print(prefix);
    identifierNode.print(prefix);
    expressionNode->print(prefix);
}

VariableDefinitionNode::~VariableDefinitionNode()
{
    if (expressionNode)
    {
        delete expressionNode;
    }
}