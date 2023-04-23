#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include <map>
#include <variant>
#include <vector>
#include <memory>

class ClassTypeInfo;
class BlockNode;
class FunctionTypeInfo;

typedef std::variant<std::string, ClassTypeInfo> typeInfo;

class ClassTypeInfo
{
public:
    std::string className;
    std::map<std::string, typeInfo> propertyInfo;
    std::map<std::string, FunctionTypeInfo> functionInfo;

    ClassTypeInfo(const std::string &name);
    ClassTypeInfo(const std::string &name, const std::map<std::string, typeInfo> &propertyInfo, const std::map<std::string, FunctionTypeInfo> &functionInfo);

    ClassTypeInfo(const ClassTypeInfo &other);
    ClassTypeInfo(ClassTypeInfo &&other);

    ClassTypeInfo &operator=(const ClassTypeInfo &other);
    ClassTypeInfo &operator=(ClassTypeInfo &&other);

    void addProperty(const std::string &name, const typeInfo &type);
    void addFunction(const std::string &name, const typeInfo &type, BlockNode *const &functionNode, const std::vector<std::pair<std::string, typeInfo>> &parameters);

    void print();
};

class FunctionTypeInfo
{
public:
    typeInfo returnType;
    BlockNode *functionNode;
    std::vector<std::pair<std::string, typeInfo>> parameters;

    FunctionTypeInfo(const typeInfo &returnType, BlockNode *const &functionNode, const std::vector<std::pair<std::string, typeInfo>> &parameters);
    void print();
};

class ClassInfo
{
public:
    ClassTypeInfo info;

    ClassInfo(const ClassTypeInfo &info);
    ClassInfo(ClassTypeInfo &&info);
    ClassInfo(const ClassInfo &other);
    ClassInfo(ClassInfo &&other);

    void addProperty(const std::string &name, const typeInfo &type);
    void addFunction(const std::string &name, const typeInfo &type, BlockNode *const &functionNode, const std::vector<std::pair<std::string, typeInfo>> &parameters);

    std::unique_ptr<ClassInfo> clone();

    ClassInfo &operator=(const ClassInfo &other);
    ClassInfo &operator=(ClassInfo &&other);
    void print();
};

#endif // CLASS_INFO_H