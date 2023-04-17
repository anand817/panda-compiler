#include <context/object.hpp>
#include <context/symbol_table.hpp>

Object::Object(const std::map<std::string, std::unique_ptr<SymbolInfo>> &properties)
{
    for (const auto &p : properties)
    {
        this->properties.emplace(p.first, p.second->clone());
    }

    this->isObject = true;
}

Object::Object(std::map<std::string, std::unique_ptr<SymbolInfo>> &&properties)
{
    this->properties = std::move(properties);
    this->isObject = true;
}

Object::Object(const allType &data)
{
    this->data = data;
    this->isObject = false;
}

Object::Object(allType &&data)
{
    this->data = std::move(data);
    this->isObject = false;
}

Object::Object(const Object &other)
{
    this->data = other.data;
    for (const auto &p : properties)
    {
        this->properties.emplace(p.first, p.second->clone());
    }
    this->isObject = other.isObject;
}

Object::Object(Object &&other)
{
    this->data = std::move(other.data);
    this->properties = std::move(other.properties);
    this->isObject = std::move(other.isObject);
}

Object &Object::operator=(const Object &other)
{
    if (this != &other)
    {
        this->data = other.data;
        for (const auto &p : properties)
        {
            this->properties.emplace(p.first, p.second->clone());
        }
        this->isObject = other.isObject;
    }

    return *this;
}

Object &Object::operator=(Object &&other)
{
    if (this != &other)
    {
        this->data = std::move(other.data);
        this->properties = std::move(other.properties);
        this->isObject = std::move(other.isObject);
    }

    return *this;
}