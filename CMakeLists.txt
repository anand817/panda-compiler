cmake_minimum_required(VERSION 3.26)
project(PandaCompiler VERSION 1.0 LANGUAGES CXX)

add_executable(panda-compiler "")
add_subdirectory(src)

include(rules/CMakeLists.txt)