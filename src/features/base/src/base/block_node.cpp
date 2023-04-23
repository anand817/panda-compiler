#include <base/nodes.hpp>
#include <context/context_handler.hpp>
#include <iostream>

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
    ContextHandler::pushContext(SCOPE_TYPE::BLOCK_SCOPE, this);
    bool stop_processing = false;
    for (StatementNode *statement : statements)
    {
        auto &context = ContextHandler::getContext(SCOPE_TYPE::BLOCK_SCOPE);
        stop_processing = context->stop_processing;
        if (stop_processing)
            break;
        statement->run();
    }
    ContextHandler::popContext();
}

void BlockNode::run(SCOPE_TYPE scope)
{
    bool stop_processing = false;
    for (StatementNode *statement : statements)
    {
        auto &context = ContextHandler::getContext(scope);
        stop_processing = context->stop_processing;

        if (stop_processing)
            break;
        statement->run();
    }
}

void BlockNode::print(std::string prefix)
{
    std::cout << prefix << "Block Node with " << statements.size() << " statements" << std::endl;
    prefix += "\t-> ";
    for (auto statement : statements)
    {
        statement->print(prefix);
    }
}

BlockNode::~BlockNode()
{
    for (StatementNode *statement : statements)
    {
        delete statement;
    }
}
