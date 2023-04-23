#include <enums/scope_type_enum.hpp>

std::ostream &operator<<(std::ostream &out, const SCOPE_TYPE &scope)
{
    switch (scope)
    {
    case SCOPE_TYPE::LOOP_SCOPE:
        out << "loop scope";
        break;
    case SCOPE_TYPE::LOOP_BLOCK_SCOPE:
        out << "loop block scope";
        break;
    case SCOPE_TYPE::FUNCTION_SCOPE:
        out << "function scope";
        break;
    case SCOPE_TYPE::BLOCK_SCOPE:
        out << "block scope";
        break;
    case SCOPE_TYPE::BRANCH_SCOPE:
        out << "branch scope";
        break;
    default:
        out << "undefined scope";
        break;
    }

    return out;
}