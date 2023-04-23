target_sources(panda-compiler PRIVATE
    src/loop/for_node.cpp
    src/loop/while_node.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)