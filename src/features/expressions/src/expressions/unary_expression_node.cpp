#include <expressions/nodes.hpp>

UnaryExpressionNode::UnaryExpressionNode(ExpressionNode *const &expression, UNARY_OPERATOR operation)
    : expression(expression),
      operation(operation) {}

UnaryExpressionNode::UnaryExpressionNode(const UnaryExpressionNode &other)
    : ExpressionNode(other),
      operation(operation),
      expression(expression->clone()) {}

UnaryExpressionNode::UnaryExpressionNode(UnaryExpressionNode &&other)
    : ExpressionNode(std::move(other)),
      operation(std::move(other.operation)),
      expression(std::move(other.expression)) {}

UnaryExpressionNode &UnaryExpressionNode::operator=(const UnaryExpressionNode &other)
{
    if (this != &other)
    {
        ExpressionNode::operator=(other);
        this->operation = other.operation;
        this->expression = other.expression->clone();
    }

    return *this;
}

UnaryExpressionNode &UnaryExpressionNode::operator=(UnaryExpressionNode &&other)
{
    if (this != &other)
    {
        ExpressionNode::operator=(std::move(other));
        this->operation = std::move(other.operation);
        this->expression = std::move(other.expression);
    }

    return *this;
}

ExpressionNode *UnaryExpressionNode::clone()
{
    return new UnaryExpressionNode(*this);
}

std::vector<std::string> UnaryExpressionNode::generateCode()
{
    return {};
}
bool UnaryExpressionNode::analyze()
{
    return true;
}
void UnaryExpressionNode::run()
{

    overload plus_overload{
        [this](int &a)
        { valueNode.assignValue(a); },
        [this](float &a)
        { valueNode.assignValue(a); },
        [this](auto &a)
        { throw "operation not allowed on this data type"; }};

    overload minus_overload{
        [this](int &a)
        { valueNode.assignValue(-a); },
        [this](float &a)
        { valueNode.assignValue(-a); },
        [this](auto &a)
        { throw "operation not allowed on this data type"; }};

    overload pre_increment_overload{
        [this](int &a)
        { valueNode.assignValue(++a); },
        [this](float &a)
        { valueNode.assignValue(++a); },
        [this](auto &a)
        { throw "operation not allowed on this data type"; }};

    overload post_increment_overload{
        [this](int &a)
        { valueNode.assignValue(a++); },
        [this](float &a)
        { valueNode.assignValue(a++); },
        [this](auto &a)
        { throw "operation not allowed on this data type"; }};

    overload pre_decrement_overload{
        [this](int &a)
        { valueNode.assignValue(--a); },
        [this](float &a)
        { valueNode.assignValue(--a); },
        [this](auto &a)
        { throw "operation not allowed on this data type"; }};

    overload post_decrement_overload{
        [this](int &a)
        { valueNode.assignValue(a--); },
        [this](float &a)
        { valueNode.assignValue(a--); },
        [this](auto &a)
        { throw "operation not allowed on this data type"; }};

    overload not_overload{
        [this](int &a)
        { valueNode.assignValue(~a); },
        [this](bool &a)
        { valueNode.assignValue(~a); },
        [this](auto &a)
        { throw "operation not allowed on this data float"; }};

    overload logical_not_overload{
        [this](int &a)
        { valueNode.assignValue(!a); },
        [this](bool &a)
        { valueNode.assignValue(!a); },
        [this](auto &a)
        { throw "operation not allowed on this data float"; }};
    expression->run();
    ValueNode &childValueNode = expression->valueNode;

    switch (operation)
    {
    case UNARY_OPERATOR::UNARY_PLUS:
        std::visit(plus_overload, childValueNode.value);
        break;
    case UNARY_OPERATOR::UNARY_MINUS:
        std::visit(minus_overload, childValueNode.value);
        break;
    case UNARY_OPERATOR::PRE_INCREMENT:
        if (!expression->isLvalue())
        {
            throw "pre increment operator cannot be used on rvalue";
        }
        std::visit(pre_increment_overload, childValueNode.value);
        expression->updateSymbol(childValueNode.type, childValueNode.value);
        break;
    case UNARY_OPERATOR::POST_INCREMENT:
        if (!expression->isLvalue())
        {
            throw "post increment operator cannot be used on rvalue";
        }
        std::visit(post_increment_overload, childValueNode.value);
        expression->updateSymbol(childValueNode.type, childValueNode.value);
        break;
    case UNARY_OPERATOR::PRE_DECREMENT:
        if (!expression->isLvalue())
        {
            throw "pre decrement operator cannot be used on rvalue";
        }
        std::visit(pre_decrement_overload, childValueNode.value);
        expression->updateSymbol(childValueNode.type, childValueNode.value);
        break;
    case UNARY_OPERATOR::POST_DECREMENT:
        if (!expression->isLvalue())
        {
            throw "post decrement operator cannot be used on rvalue";
        }
        std::visit(post_decrement_overload, childValueNode.value);
        expression->updateSymbol(childValueNode.type, childValueNode.value);
        break;
    case UNARY_OPERATOR::NOT:
        std::visit(not_overload, childValueNode.value);
        break;
    case UNARY_OPERATOR::LOGICAL_NOT:
        std::visit(logical_not_overload, childValueNode.value);
        break;
    default:
        throw "undefined operator";
        break;
    }
}

bool UnaryExpressionNode::isLvalue()
{
    if ((operation == UNARY_OPERATOR::PRE_DECREMENT || operation == UNARY_OPERATOR::PRE_INCREMENT) && expression->isLvalue())
        return true;
    return false;
}

void UnaryExpressionNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    if (!this->isLvalue())
    {
        throw "unary expression with given operator is not an lvalue";
    }
    expression->updateSymbol(dataType, data);
}

std::unique_ptr<SymbolInfo> &UnaryExpressionNode::getSymbol()
{
    if (!this->isLvalue())
    {
        throw "unary expression with given operator is not an lvalue";
    }
    return expression->getSymbol();
}

void UnaryExpressionNode::print(std::string prefix)
{
    std::cout << prefix << "Unary Expression Node" << std::endl;
    prefix += "\t-> ";
    std::cout << prefix << operation << std::endl;
    expression->print(prefix);
}