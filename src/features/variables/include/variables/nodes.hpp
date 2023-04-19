#include <base/nodes.hpp>
#include <utils/nodes.hpp>

class VariableDeclarationNode : public DeclarationNode
{
public:
    VariableDeclarationNode(const TypeNode &type, const IdentifierNode &identifier);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
};

class VariableDefinitionNode : public VariableDeclarationNode
{
public:
    VariableDefinitionNode(const TypeNode &type, const IdentifierNode &identifier);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
};