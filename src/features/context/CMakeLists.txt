target_sources(panda-compiler PRIVATE
    src/context/context.cpp
    src/context/context_handler.cpp
    src/context/symbol_table.cpp
    src/context/class_table.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)