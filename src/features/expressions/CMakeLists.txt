target_sources(panda-compiler PRIVATE
    src/expressions/expression_node.cpp
    src/expressions/unary_expression_node.cpp
    src/expressions/binary_expression_node.cpp
    src/expressions/identifier_expression_node.cpp
    src/expressions/function_call_node.cpp
    src/expressions/print_node.cpp
    src/expressions/input_node.cpp
    src/expressions/object_variable_node.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)