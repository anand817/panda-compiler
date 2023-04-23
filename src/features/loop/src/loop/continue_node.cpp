#include <loop/nodes.hpp>
#include <context/context_handler.hpp>

ContinueNode::ContinueNode()
    : StatementNode() {}

ContinueNode::ContinueNode(const ContinueNode &other)
    : StatementNode(other) {}

ContinueNode::ContinueNode(ContinueNode &&other)
    : StatementNode(std::move(other)) {}

ContinueNode &ContinueNode::operator=(const ContinueNode &other)
{
    if (this != &other)
    {
        StatementNode::operator=(other);
    }
    return *this;
}

ContinueNode &ContinueNode::operator=(ContinueNode &&other)
{
    if (this != &other)
    {
        StatementNode::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::string> ContinueNode::generateCode()
{
    return {};
}

bool ContinueNode::analyze()
{
    return true;
}

void ContinueNode::run()
{
    std::unique_ptr<Context> &context = ContextHandler::getContext(SCOPE_TYPE::LOOP_BLOCK_SCOPE);
    if (!context)
    {
        throw "break statement could only be used inside block scope of a loop";
    }
    ContextHandler::returnTillContext(SCOPE_TYPE::LOOP_BLOCK_SCOPE);
}

void ContinueNode::print(std::string prefix)
{
    std::cout << prefix << "Continue node" << std::endl;
}