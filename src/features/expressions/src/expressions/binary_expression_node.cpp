#include <expressions/nodes.hpp>

BinaryExpressionNode::BinaryExpressionNode(ExpressionNode *const &left_expression, ExpressionNode *const &right_expression, BINARY_OPERATOR operation)
    : left_expression(left_expression),
      right_expression(right_expression),
      operation(operation) {}

BinaryExpressionNode::BinaryExpressionNode(const BinaryExpressionNode &other)
    : ExpressionNode(other),
      left_expression(other.left_expression->clone()),
      right_expression(other.right_expression->clone()),
      operation(other.operation) {}

BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode &&other)
    : ExpressionNode(std::move(other)),
      left_expression(std::move(other.left_expression)),
      right_expression(std::move(other.right_expression)),
      operation(std::move(other.operation)) {}

BinaryExpressionNode &BinaryExpressionNode::operator=(const BinaryExpressionNode &other)
{
    if (this != &other)
    {
        ExpressionNode::operator=(other);
        this->left_expression = other.left_expression->clone();
        this->right_expression = other.right_expression->clone();
        this->operation = other.operation;
    }

    return *this;
}

BinaryExpressionNode &BinaryExpressionNode::operator=(BinaryExpressionNode &&other)
{
    if (this != &other)
    {
        ExpressionNode::operator=(std::move(other));
        this->left_expression = std::move(other.left_expression);
        this->right_expression = std::move(other.right_expression);
        this->operation = std::move(other.operation);
    }

    return *this;
}

ExpressionNode *BinaryExpressionNode::clone()
{
    return new BinaryExpressionNode(*this);
}

std::vector<std::string> BinaryExpressionNode::generateCode()
{
    return {};
}
bool BinaryExpressionNode::analyze()
{
    return true;
}
void BinaryExpressionNode::run()
{
    left_expression->run();
    // copy the value to a new valueNode as it may get updated after running right expression
    ValueNode leftChildValueNode(left_expression->valueNode);
    right_expression->run();
    ValueNode rightChildValueNode(right_expression->valueNode);

    overload add_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a + b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a + b); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue(a + b); },
        [this](std::string &a, char &b)
        { valueNode.assignValue(a + b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload subtract_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a - b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a - b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload multiply_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a * b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a * b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload divide_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a / b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a / b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload modulus_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a / b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload assign_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a = b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a = b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a = b); },
        [this](char &a, char &b)
        { valueNode.assignValue(a = b); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue(a = b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload or_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a | b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a | b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload logical_or_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a || b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a || b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload and_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a & b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a & b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload logical_and_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a && b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a && b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload xor_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a ^ b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a ^ b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload shift_left_overload{
        [this](int &a, int &b)
        {
            valueNode.assignValue((a << b));
        },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload shift_right_overload{
        [this](int &a, int &b)
        {
            valueNode.assignValue((a >> b));
        },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload greater_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a > b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a > b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a > b); },
        [this](char &a, char &b)
        { valueNode.assignValue(a > b); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue(a > b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload greater_equal_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a >= b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a >= b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a >= b); },
        [this](char &a, char &b)
        { valueNode.assignValue(a >= b); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue(a >= b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload lesser_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a < b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a < b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a < b); },
        [this](char &a, char &b)
        { valueNode.assignValue(a < b); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue(a < b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload lesser_equal_overload{
        [this](int &a, int &b)
        { valueNode.assignValue(a <= b); },
        [this](float &a, float &b)
        { valueNode.assignValue(a <= b); },
        [this](bool &a, bool &b)
        { valueNode.assignValue(a <= b); },
        [this](char &a, char &b)
        { valueNode.assignValue(a <= b); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue(a <= b); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload equal_overload{
        [this](int &a, int &b)
        { valueNode.assignValue((a == b)); },
        [this](float &a, float &b)
        { valueNode.assignValue((a == b)); },
        [this](bool &a, bool &b)
        { valueNode.assignValue((a == b)); },
        [this](char &a, char &b)
        { valueNode.assignValue((a == b)); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue((a == b)); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    overload not_equal_overload{
        [this](int &a, int &b)
        { valueNode.assignValue((a != b)); },
        [this](float &a, float &b)
        { valueNode.assignValue((a != b)); },
        [this](bool &a, bool &b)
        { valueNode.assignValue((a != b)); },
        [this](char &a, char &b)
        { valueNode.assignValue((a != b)); },
        [this](std::string &a, std::string &b)
        { valueNode.assignValue((a != b)); },
        [this](auto &a, auto &b)
        { throw "operation not allowed on this pair of data type"; }};

    switch (operation)
    {
    case BINARY_OPERATOR::ADD:
        std::visit(add_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::SUBTRACT:
        std::visit(subtract_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::MULTIPLY:
        std::visit(multiply_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::DIVIDE:
        std::visit(divide_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::MODULUS:
        std::visit(modulus_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::ASSIGN:
        if (!left_expression->isLvalue())
        {
            throw "assign operator cannot be used on rvalue";
        }
        std::visit(assign_overload, leftChildValueNode.value, rightChildValueNode.value);
        left_expression->updateSymbol(leftChildValueNode.type, leftChildValueNode.value);
        break;
    case BINARY_OPERATOR::OR:
        std::visit(or_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::LOGICAL_OR:
        std::visit(logical_or_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::AND:
        std::visit(and_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::LOGICAL_AND:
        std::visit(logical_and_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::XOR:
        std::visit(xor_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::SHIFT_LEFT:
        std::visit(shift_left_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::SHIFT_RIGHT:
        std::visit(shift_right_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::GREATER:
        std::visit(greater_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::GREATER_EQUAL:
        std::visit(greater_equal_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::LESSER:
        std::visit(lesser_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::LESSER_EQUAL:
        std::visit(lesser_equal_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::EQUAL:
        std::visit(equal_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    case BINARY_OPERATOR::NOT_EQUAL:
        std::visit(not_equal_overload, leftChildValueNode.value, rightChildValueNode.value);
        break;
    default:
        throw "undefined operator";
        break;
    }
}

bool BinaryExpressionNode::isLvalue()
{
    // every binary expression is a rvalue;
    return false;
}

void BinaryExpressionNode::updateSymbol(const typeInfo &dataType, const valueType &data)
{
    throw "binary expression is not an lvalue";
}

std::unique_ptr<SymbolInfo> &BinaryExpressionNode::getSymbol()
{
    throw "binary expression is not an lvalue";
}

void BinaryExpressionNode::print(std::string prefix)
{
    std::cout << prefix << "Binary Expression Node" << std::endl;
    prefix += "\t-> ";
    ExpressionNode::print(prefix);
    std::cout << prefix << operation << std::endl;
    left_expression->print(prefix);
    right_expression->print(prefix);
}