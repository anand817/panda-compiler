#ifndef UTILS_SCOPE_TYPE_ENUM_H
#define UTILS_SCOPE_TYPE_ENUM_H

#include <iostream>

enum class SCOPE_TYPE
{
    LOOP_SCOPE,
    FUNCTION_SCOPE,
    BLOCK_SCOPE,
    BRANCH_SCOPE
};

std::ostream &operator<<(std::ostream &out, const SCOPE_TYPE &operation);

#endif // UTILS_SCOPE_TYPE_ENUM_H