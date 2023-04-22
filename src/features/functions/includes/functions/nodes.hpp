#include <base/nodes.hpp>
#include <variables/nodes.hpp>

typedef std::vector<VariableDeclarationNode> VariableList;

class FunctionDeclarationNode : public DeclarationNode
{
public:
    VariableList variableList;
    BlockNode *functionBlockNode;

    FunctionDeclarationNode(const TypeNode &typeNode, const IdentifierNode &identifierNode, const VariableList &variableList, BlockNode *const &functionBlockNode);

    void assignBody(BlockNode *const &functionBlockNode);
    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
};