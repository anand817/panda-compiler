#include <expressions/nodes.hpp>
#include <context/object.hpp>

PrintNode::PrintNode(const ArgumentList &argumentList)
    : FunctionCallNode(IdentifierNode("print"), argumentList) {}

PrintNode::PrintNode(const PrintNode &other)
    : FunctionCallNode(other) {}

PrintNode::PrintNode(PrintNode &&other)
    : FunctionCallNode(std::move(other)) {}

PrintNode &PrintNode::operator=(const PrintNode &other)
{
    if (this != &other)
    {
        FunctionCallNode::operator=(other);
    }
    return *this;
}

PrintNode &PrintNode::operator=(PrintNode &&other)
{
    if (this != &other)
    {
        FunctionCallNode::operator=(std::move(other));
    }
    return *this;
}

ExpressionNode *PrintNode::clone()
{
    return new PrintNode(*this);
}

std::vector<std::string> PrintNode::generateCode()
{
    return {};
}

bool PrintNode::analyze()
{
    return true;
}

void PrintNode::run()
{
    typeNode.type = VOID_TYPE;
    for (auto expression : argumentList)
    {
        expression->run();
        std::cout << expression->valueNode.value << " ";
    }
    std::cout << std::endl;
}

void PrintNode::print(std::string prefix)
{
    std::cout << prefix << "print Node" << std::endl;
    prefix += "\t-> ";
    IdentifierExpressionNode::print(prefix);
    typeNode.print(prefix);
    std::cout << prefix << "expressions: " << std::endl;
    for (auto expression : argumentList)
    {
        expression->print(prefix);
    }
}

bool PrintNode::isLvalue()
{
    return false;
}

void PrintNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    throw "function call is not an lvalue";
}