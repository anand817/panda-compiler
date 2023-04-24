#include <context/object.hpp>
#include <enums/type_enum.hpp>
#include <context/context_handler.hpp>
#include <iostream>

// typeInfo getType(const valueType &value)
// {
//     typeInfo type_value = INT_TYPE;
//     overload type_overload2{
//         [&type_value](int &a)
//         { type_value = INT_TYPE; },
//         [&type_value](float &a)
//         { type_value = FLOAT_TYPE; },
//         [&type_value](std::string &a)
//         { type_value = STRING_TYPE; },
//         [&type_value](bool &a)
//         { type_value = BOOL_TYPE; },
//         [&type_value](char &a)
//         { type_value = CHAR_TYPE; },
//         [&type_value, &value](std::shared_ptr<objectType> &a)
//         {
//             auto objectClassName = std::get<std::shared_ptr<objectType>>(value)->className;
//             auto &classInfo = ContextHandler::findClass(objectClassName);
//             if (classInfo == nullptr)
//             {
//                 throw "class is undefined";
//             }
//             type_value = classInfo->info;
//         }};
//     std::visit(type_overload2, value);
//     return type_value;
// }

objectType::objectType()
    : className(),
      parameters(),
      info("") {}

objectType::objectType(const std::string &className, const std::map<std::string, valueType> parameters, const ClassTypeInfo &info)
    : className(className),
      parameters(parameters),
      info(className) {}

objectType::objectType(const objectType &other)
    : className(other.className),
      parameters(other.parameters),
      info(other.info) {}

objectType::objectType(objectType &&other)
    : className(std::move(other.className)),
      parameters(std::move(other.parameters)),
      info(std::move(other.info)) {}

objectType &objectType::operator=(const objectType &other)
{
    if (this != &other)
    {
        this->className = other.className;
        this->parameters = other.parameters;
        this->info = other.info;
    }
    return *this;
}

objectType &objectType::operator=(objectType &&other)
{
    if (this != &other)
    {
        this->className = std::move(other.className);
        this->parameters = std::move(other.parameters);
        this->info = std::move(other.info);
    }
    return *this;
}

std::string getTypeString(const typeInfo &type)
{
    if (std::holds_alternative<std::string>(type))
    {
        return std::get<std::string>(type);
    }
    return std::get<ClassTypeInfo>(type).className;
}

std::ostream &operator<<(std::ostream &out, objectType &a)
{
    out << "<";
    out << a.className;
    out << ">";
    out << "( ";
    for (auto params : a.parameters)
    {
        out << params.first << " : " << params.second << ",";
    }
    out << ")";
    return out;
}

std::ostream &operator<<(std::ostream &out, const valueType &value)
{
    overload print_overload{
        [&out](const std::shared_ptr<objectType> &a)
        {
            out << "<";
            out << a->className;
            out << ">";
            out << "( ";
            for (auto params : a->parameters)
            {
                out << params.first << " : " << params.second << ",";
            }
            out << ")";
        },
        [&out](auto &a)
        { out << a; }};

    std::visit(print_overload, value);
    return out;
}

std::istream &operator>>(std::istream &in, valueType &value)
{
    overload input_overload{
        [&in](std::shared_ptr<objectType> &a)
        { throw "object input cannot be taken"; },
        [&in](auto &a)
        { in >> a; }};

    std::visit(input_overload, value);
    return in;
}