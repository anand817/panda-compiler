#include <context/class_table.hpp>
#include <context/object.hpp>
#include <iostream>

FunctionTypeInfo::FunctionTypeInfo(const typeInfo &returnType, BlockNode *const &functionNode, const std::vector<std::pair<std::string, typeInfo>> &parameters)
    : returnType(returnType),
      functionNode(functionNode),
      parameters(parameters) {}

void FunctionTypeInfo::print()
{
    std::cout << getTypeString(returnType) << " ( ";
    for (auto parameter : parameters)
    {
        std::cout << parameter.first << " : " << getTypeString(parameter.second) << ",";
    }
    std::cout << " ) ";
}

ClassTypeInfo::ClassTypeInfo(const std::string &name)
    : className(name),
      propertyInfo(),
      functionInfo()
{
}

ClassTypeInfo::ClassTypeInfo(const std::string &name, const std::map<std::string, typeInfo> &propertyInfo, const std::map<std::string, FunctionTypeInfo> &functionInfo)
    : className(name),
      propertyInfo(propertyInfo),
      functionInfo(functionInfo) {}

ClassTypeInfo::ClassTypeInfo(const ClassTypeInfo &other)
    : className(other.className),
      propertyInfo(other.propertyInfo),
      functionInfo(other.functionInfo) {}

ClassTypeInfo::ClassTypeInfo(ClassTypeInfo &&other)
    : className(std::move(other.className)),
      propertyInfo(std::move(other.propertyInfo)),
      functionInfo(std::move(other.functionInfo)) {}

ClassTypeInfo &ClassTypeInfo::operator=(const ClassTypeInfo &other)
{
    if (this != &other)
    {
        className = other.className;
        propertyInfo = other.propertyInfo;
        functionInfo = other.functionInfo;
    }

    return *this;
}

ClassTypeInfo &ClassTypeInfo::operator=(ClassTypeInfo &&other)
{
    if (this != &other)
    {
        className = std::move(other.className);
        propertyInfo = std::move(other.propertyInfo);
        functionInfo = std::move(other.functionInfo);
    }

    return *this;
}

void ClassTypeInfo::addProperty(const std::string &name, const typeInfo &type)
{
    propertyInfo.emplace(name, type);
}

void ClassTypeInfo::addFunction(const std::string &name, const typeInfo &type, BlockNode *const &functionNode, const std::vector<std::pair<std::string, typeInfo>> &parameters)
{
    functionInfo.emplace(name, FunctionTypeInfo(type, functionNode, parameters));
}

void ClassTypeInfo::print()
{
    std::cout << "info: " << className << std::endl;
    std::cout << "variables: " << std::endl;
    for (auto &p : propertyInfo)
    {
        std::cout << p.first << " : " << getTypeString(p.second) << std::endl;
    }
    std::cout << std::endl;
    std::cout << "functions: " << std::endl;
    for (auto &p : functionInfo)
    {
        std::cout << p.first << " : ";
        p.second.print();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

ClassInfo::ClassInfo(const ClassTypeInfo &info)
    : info(info) {}

ClassInfo::ClassInfo(ClassTypeInfo &&info)
    : info(std::move(info)) {}

ClassInfo::ClassInfo(const ClassInfo &other)
    : info(other.info) {}

ClassInfo::ClassInfo(ClassInfo &&other)
    : info(std::move(other.info)) {}

void ClassInfo::addProperty(const std::string &name, const typeInfo &type)
{
    this->info.addProperty(name, type);
}

void ClassInfo::addFunction(const std::string &name, const typeInfo &type, BlockNode *const &functionNode, const std::vector<std::pair<std::string, typeInfo>> &parameters)
{
    this->info.addFunction(name, type, functionNode, parameters);
}

std::unique_ptr<ClassInfo> ClassInfo::clone()
{
    return std::make_unique<ClassInfo>(*this);
}

ClassInfo &ClassInfo::operator=(const ClassInfo &other)
{
    if (this != &other)
    {
        this->info = other.info;
    }
    return *this;
}

ClassInfo &ClassInfo::operator=(ClassInfo &&other)
{
    if (this != &other)
    {
        this->info = std::move(other.info);
    }
    return *this;
}

void ClassInfo::print()
{
    info.print();
}