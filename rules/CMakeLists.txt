find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(lexer ${CMAKE_CURRENT_LIST_DIR}/panda.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.hpp)
bison_target(parser ${CMAKE_CURRENT_LIST_DIR}/panda.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)
message(STATUS "flex outputs ${FLEX_lexer_OUTPUTS}")
message(STATUS "parser outputs ${BISON_parser_OUTPUTS}")
target_sources(panda-compiler PRIVATE
    ${FLEX_lexer_OUTPUTS}
)
