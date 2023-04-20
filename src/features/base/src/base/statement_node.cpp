#include <base/nodes.hpp>

std::vector<std::string> StatementNode::generateCode()
{
    // defines empty string
    return {};
}

bool StatementNode::analyze()
{
    return true;
}

void StatementNode::run()
{
    // defines empty string
}

void StatementNode::print(std::string prefix)
{
    std::cout << prefix << "Empty statement" << std::endl;
}