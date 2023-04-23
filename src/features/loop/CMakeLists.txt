target_sources(panda-compiler PRIVATE
    src/loop/for_node.cpp
    src/loop/while_node.cpp
    src/loop/break_node.cpp
    src/loop/continue_node.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)