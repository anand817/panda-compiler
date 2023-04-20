target_sources(panda-compiler PRIVATE
    src/utils/nodes.cpp
    src/utils/type_enums.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)