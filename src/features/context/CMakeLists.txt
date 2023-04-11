target_sources(panda-compiler PUBLIC
    src/context/context_handler.cpp src
    src/context/context.cpp
    src/context/symbol_table.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)