target_sources(panda-compiler PRIVATE
    src/utils/nodes.cpp
    src/utils/type_enums.cpp
    src/utils/operation_enum.cpp
    src/utils/scope_type_enum.cpp
)

target_include_directories(panda-compiler PRIVATE includes/)