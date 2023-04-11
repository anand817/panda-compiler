#include <base/nodes.hpp>
#include <vector>
#include <string>

ProgrammeNode::ProgrammeNode()
{
    statements.clear();
}

std::vector<std::string> ProgrammeNode::generateCode()
{
    std::vector<std::string> code, statementCode;

    for (StatementNode *statement : statements)
    {
        statementCode = statement->generateCode();
        code.insert(code.end(), statementCode.begin(), statementCode.end());
    }

    return code;
}

void ProgrammeNode::run()
{
    // TODO: needs to be updates to find `main` function and run the function
    for (StatementNode *statement : statements)
    {
        statement->run();
    }
}