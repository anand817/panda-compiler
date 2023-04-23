#include <expressions/nodes.hpp>

InputNode::InputNode(const ArgumentList &argumentList)
    : FunctionCallNode(IdentifierNode("input"), argumentList) {}

InputNode::InputNode(const InputNode &other)
    : FunctionCallNode(other) {}

InputNode::InputNode(InputNode &&other)
    : FunctionCallNode(std::move(other)) {}

InputNode &InputNode::operator=(const InputNode &other)
{
    if (this != &other)
    {
        FunctionCallNode::operator=(other);
    }
    return *this;
}
InputNode &InputNode::operator=(InputNode &&other)
{
    if (this != &other)
    {
        FunctionCallNode::operator=(std::move(other));
    }
    return *this;
}

ExpressionNode *InputNode::clone()
{
    return new InputNode(*this);
}

std::vector<std::string> InputNode::generateCode()
{
    return {};
}

bool InputNode::analyze()
{
    return true;
}
void InputNode::run()
{
    for (auto &expression : argumentList)
    {
        expression->run();
        auto &symbolInfo = expression->getSymbol(); // throw error when expression is lvalue
        if (symbolInfo == nullptr)
        {
            throw "identifier not found";
        }
        VariableInfo *variableInfo = dynamic_cast<VariableInfo *>(symbolInfo.get());
        if (!variableInfo)
        {
            throw "identifier is not a variable ( check if its a function )";
        }
        std::cin >> variableInfo->valueContainer;
    }
}

void InputNode::print(std::string prefix)
{
    std::cout << prefix << "input Node" << std::endl;
    prefix += "\t-> ";
    IdentifierExpressionNode::print(prefix);
    typeNode.print(prefix);
    std::cout << prefix << "expressions: " << std::endl;
    for (auto expression : argumentList)
    {
        expression->print(prefix);
    }
}

bool InputNode::isLvalue()
{
    return false;
}

void InputNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    throw "input function is not an lvalue";
}

std::unique_ptr<SymbolInfo> &InputNode::getSymbol()
{
    throw "input function is not an lvalue";
}
