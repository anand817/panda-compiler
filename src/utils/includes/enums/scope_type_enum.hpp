#include <iostream>

enum class SCOPE_TYPE
{
    LOOP_SCOPE,
    FUNCTION_SCOPE,
    BLOCK_SCOPE,
    BRANCH_SCOPE
};

std::ostream &operator<<(std::ostream &out, const SCOPE_TYPE &operation);