cmake_minimum_required(VERSION 3.16)
project(PandaCompiler VERSION 1.0 LANGUAGES CXX)

add_executable(panda-compiler "")

add_subdirectory(rules)
add_subdirectory(src)
