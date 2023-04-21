#ifndef UTILS_OPERATION_ENUM_H
#define UTILS_OPERATION_ENUM_H

#include <string>
#include <iostream>

// binary operators

enum class BINARY_OPERATOR
{
    ADD,           // a + b
    SUBTRACT,      // a - b
    MULTIPLY,      // a * b
    DIVIDE,        // a / b
    MODULUS,       // a % b
    ASSIGN,        // a = b
    OR,            // a | b
    LOGICAL_OR,    // a || b
    AND,           // a & b
    LOGICAL_AND,   // a && b
    XOR,           // a ^ b
    SHIFT_LEFT,    // a << b
    SHIFT_RIGHT,   // a >> b
    GREATER,       // a > b
    GREATER_EQUAL, // a >= b
    LESSER,        // a < b
    LESSER_EQUAL,  // a <= b
    EQUAL,         // a = b
    NOT_EQUAL,     // a != b
};

std::ostream &operator<<(std::ostream &out, const BINARY_OPERATOR &operation);
// unar operators

enum class UNARY_OPERATOR
{
    UNARY_PLUS,     // +a
    UNARY_MINUS,    // -a
    PRE_INCREMENT,  // ++a
    POST_INCREMENT, // a++
    PRE_DECREMENT,  // --a
    POST_DECREMENT, // a--
    NOT,            // ~a
    LOGICAL_NOT     // !a
};

std::ostream &operator<<(std::ostream &out, const UNARY_OPERATOR &operation);

#endif // UTILS_OPERATION_ENUM_H
