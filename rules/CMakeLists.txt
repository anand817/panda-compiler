find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser panda.y src/rules/panda-parser.cpp DEFINES_FILE src/rules/panda-parser.hpp)
FLEX_TARGET(lexer panda.l src/rules/panda-lexer.cpp)
