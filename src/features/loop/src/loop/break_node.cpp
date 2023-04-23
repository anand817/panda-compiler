#include <loop/nodes.hpp>
#include <context/context_handler.hpp>

BreakNode::BreakNode()
    : StatementNode() {}

BreakNode::BreakNode(const BreakNode &other)
    : StatementNode(other) {}

BreakNode::BreakNode(BreakNode &&other)
    : StatementNode(std::move(other)) {}

BreakNode &BreakNode::operator=(const BreakNode &other)
{
    if (this != &other)
    {
        StatementNode::operator=(other);
    }
    return *this;
}

BreakNode &BreakNode::operator=(BreakNode &&other)
{
    if (this != &other)
    {
        StatementNode::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::string> BreakNode::generateCode()
{
    return {};
}

bool BreakNode::analyze()
{
    return true;
}

void BreakNode::run()
{
    std::unique_ptr<Context> &context = ContextHandler::getContext(SCOPE_TYPE::LOOP_SCOPE);
    if (!context)
    {
        throw "break statement could only be used inside scope of a loop";
    }
    ContextHandler::returnTillContext(SCOPE_TYPE::LOOP_SCOPE);
}

void BreakNode::print(std::string prefix)
{
    std::cout << prefix << "Break node" << std::endl;
}