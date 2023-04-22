find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rules/src ${CMAKE_CURRENT_BINARY_DIR}/rules/include ${CMAKE_CURRENT_BINARY_DIR}/rules/reports)

flex_target(lexer ${CMAKE_CURRENT_LIST_DIR}/panda.l ${CMAKE_CURRENT_BINARY_DIR}/rules/src/lexer.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/rules/include/lexer.hpp)
bison_target(parser ${CMAKE_CURRENT_LIST_DIR}/panda.y ${CMAKE_CURRENT_BINARY_DIR}/rules/src/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/rules/include/parser.hpp VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/rules/reports/parser.report)

message(STATUS "flex outputs ${FLEX_lexer_OUTPUTS}")
message(STATUS "parser outputs ${BISON_parser_OUTPUTS}")
target_sources(panda-compiler PRIVATE
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)

target_include_directories(panda-compiler PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/rules/include)