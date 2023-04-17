#ifndef OBJECT_H
#define OBJECT_H

#include <variant>
#include <map>
#include <memory>

class SymbolInfo;

typedef std::variant<int, float, std::string, bool, char> allType;
class Object
{
public:
    std::map<std::string, std::unique_ptr<SymbolInfo>> properties;
    allType data;
    bool isObject = false;

    Object(const std::map<std::string, std::unique_ptr<SymbolInfo>> &properties);
    Object(std::map<std::string, std::unique_ptr<SymbolInfo>> &&properties);
    Object(const allType &data);
    Object(allType &&data);
    Object(const Object &other);
    Object(Object &&other);

    Object &operator=(Object &&other);
    Object &operator=(const Object &other);
};

#endif // OBJECT_H