#include <base/nodes.hpp>

BlockNode::BlockNode() : statements({}) {}

BlockNode::BlockNode(const StatementList &statementList) : statements(statementList) {}

std::vector<std::string> BlockNode::generateCode()
{
    std::vector<std::string> code, statementCode;

    for (StatementNode *statement : statements)
    {
        statementCode = std::move(statement->generateCode());
        code.insert(code.end(), statementCode.begin(), statementCode.end());
    }

    return code;
}

bool BlockNode::analyze()
{
    for (StatementNode *statement : statements)
    {
        // if any statement analyze returns false and this returns false
        if (!statement->analyze())
            return false;
    }

    return true;
}

void BlockNode::run()
{
    for (StatementNode *statement : statements)
    {
        statement->run();
    }
}

BlockNode::~BlockNode()
{
    for (StatementNode *statement : statements)
    {
        delete statement;
    }
}
