target_sources(panda-compiler PRIVATE
    src/base/statement_node.cpp
    src/base/block_node.cpp
    src/base/declaration_node.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)