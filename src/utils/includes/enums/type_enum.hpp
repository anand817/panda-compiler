#ifndef UTILS_TYPE_ENUM_H
#define UTILS_TYPE_ENUM_H

#include <string>
#include <context/object.hpp>

const std::string INT_TYPE = "int";
const std::string FLOAT_TYPE = "float";
const std::string CHAR_TYPE = "char";
const std::string BOOL_TYPE = "bool";
const std::string STRING_TYPE = "string";
const std::string VOID_TYPE = "void";
// objects types are named after their class name

valueType getDefaultValue(const std::string type);

#endif // UTILS_TYPE_ENUM_H