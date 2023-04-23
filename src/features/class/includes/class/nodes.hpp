#include <base/nodes.hpp>

typedef std::vector<DeclarationNode *> DeclarationList;

class ClassDefinitionNode : public StatementNode
{
public:
    IdentifierNode identifierNode;
    DeclarationList declarations;

    ClassDefinitionNode(const IdentifierNode &identifierNode, const DeclarationList &declarations);

    virtual std::vector<std::string> generateCode();
    virtual bool analyze();
    virtual void run();
    virtual void print(std::string prefix);
};