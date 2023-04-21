#include <enums/operation_enum.hpp>

std::ostream &operator<<(std::ostream &out, const BINARY_OPERATOR &operation)
{
    switch (operation)
    {
    case BINARY_OPERATOR::ADD:
        out << "add (+)";
        break;
    case BINARY_OPERATOR::SUBTRACT:
        out << "subtract (-)";
        break;
    case BINARY_OPERATOR::MULTIPLY:
        out << "multiply (*)";
        break;
    case BINARY_OPERATOR::DIVIDE:
        out << "divide (/)";
        break;
    case BINARY_OPERATOR::MODULUS:
        out << "modulus (%)";
        break;
    case BINARY_OPERATOR::ASSIGN:
        out << "assign (=)";
        break;
    case BINARY_OPERATOR::OR:
        out << "or (|)";
        break;
    case BINARY_OPERATOR::LOGICAL_OR:
        out << "logical or (||)";
        break;
    case BINARY_OPERATOR::AND:
        out << "and (&)";
        break;
    case BINARY_OPERATOR::LOGICAL_AND:
        out << "logical and (&&)";
        break;
    case BINARY_OPERATOR::XOR:
        out << " xor (^)";
        break;
    case BINARY_OPERATOR::SHIFT_LEFT:
        out << "shift left (<<)";
        break;
    case BINARY_OPERATOR::SHIFT_RIGHT:
        out << "shift right (>>)";
        break;
    case BINARY_OPERATOR::GREATER:
        out << "greater (>)";
        break;
    case BINARY_OPERATOR::GREATER_EQUAL:
        out << "greater equal (>=)";
        break;
    case BINARY_OPERATOR::LESSER:
        out << "lesser (<)";
        break;
    case BINARY_OPERATOR::LESSER_EQUAL:
        out << "lesser equal (<=)";
        break;
    case BINARY_OPERATOR::EQUAL:
        out << "equal (==)";
        break;
    case BINARY_OPERATOR::NOT_EQUAL:
        out << "not equal (||)";
        break;
    default:
        out << "undefined operation";
        break;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const UNARY_OPERATOR &operation)
{
    switch (operation)
    {
    case UNARY_OPERATOR::UNARY_PLUS:
        out << "unary plus +[]";
        break;
    case UNARY_OPERATOR::UNARY_MINUS:
        out << "unary minus -[]";
        break;
    case UNARY_OPERATOR::PRE_INCREMENT:
        out << "pre increment ++[]";
        break;
    case UNARY_OPERATOR::POST_INCREMENT:
        out << "post increment []++";
        break;
    case UNARY_OPERATOR::PRE_DECREMENT:
        out << "pre decrement --[]";
        break;
    case UNARY_OPERATOR::POST_DECREMENT:
        out << "post decrement []--";
        break;
    case UNARY_OPERATOR::NOT:
        out << "not (~)";
        break;
    case UNARY_OPERATOR::LOGICAL_NOT:
        out << "logical not (!)";
        break;
    default:
        out << "undefined operation";
        break;
    }
    return out;
}