target_sources(panda-compiler PRIVATE
    src/variables/variable_declaration_node.cpp
    src/variables/variable_definition_node.cpp
    src/variables/object_declaration_node.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)