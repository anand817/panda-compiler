#include <base/nodes.hpp>
#include <utils/nodes.hpp>

class VariableDeclarationNode : public DeclarationNode
{
public:
    VariableDeclarationNode(TypeNode *const &type, IdentifierNode *const &identifier);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
};

class VariableDefinitionNode : public VariableDeclarationNode
{
public:
    VariableDefinitionNode(TypeNode *const &type, IdentifierNode *const &identifier);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
};