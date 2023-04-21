#include <context/context_handler.hpp>

ContextHandler::ContextHandler() : contextCounter(0), contextStack({}), poppedContextStack({}) {}

ContextHandler &ContextHandler::getInstance()
{
    static ContextHandler instance;
    return instance;
}

void ContextHandler::pushContextImpl()
{
    contextStack.emplace_back(contextCounter);
    contextCounter += 1;
}

void ContextHandler::pushContext()
{
    ContextHandler &instance = getInstance();
    instance.pushContextImpl();
}

void ContextHandler::popContextImpl()
{
    if (contextStack.empty())
    {
        throw "empty context stack";
    }
    poppedContextStack.emplace_back(std::move(contextStack.back()));
    contextStack.pop_back();
}

void ContextHandler::popContext()
{
    ContextHandler &instance = getInstance();
    instance.popContextImpl();
}

// DON'T : assign variable in the returend symbolinfo struct
// as the returned symbolinfo can be of different context than the current
std::unique_ptr<SymbolInfo> &ContextHandler::findSymbolImpl(const std::string &identifier)
{
    static std::unique_ptr<SymbolInfo> not_found;

    // iterate in reverse direction to get the closest symbol reference
    for (auto it = contextStack.rbegin(); it != contextStack.rend(); it++)
    {
        if (it->symbolTable.find(identifier) != it->symbolTable.end())
        {
            return it->symbolTable[identifier];
        }
    }

    return not_found;
}

std::unique_ptr<SymbolInfo> &ContextHandler::findSymbol(const std::string &identifier)
{
    ContextHandler &instance = getInstance();
    return instance.findSymbolImpl(identifier);
}

Context &ContextHandler::getContext()
{
    return contextStack.back();
}

void ContextHandler::printTableImpl()
{
    for (auto context : poppedContextStack)
    {
        context.print();
    }
}

void ContextHandler::printTable()
{
    ContextHandler &instance = getInstance();
    instance.printTableImpl();
}

void ContextHandler::addSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data)
{
    Context &context = getInstance().getContext();
    context.addSymbol(identifier, dataType, data);
}

void ContextHandler::addSymbol(const std::string &identifier, const typeInfo &dataType, const std::vector<std::string> &parameterList)
{
    Context &context = getInstance().getContext();
    context.addSymbol(identifier, dataType, parameterList);
}

void ContextHandler::updateSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data)
{
    Context &context = getInstance().getContext();
    std::unique_ptr<SymbolInfo> &symbolInfo = findSymbol(identifier);
    if (symbolInfo == nullptr)
    {
        throw "identifier " + identifier + " not found";
    }
    if (getTypeString(symbolInfo->dataType) != getTypeString(dataType))
    {
        throw "unmatching type of variable " + identifier + " while assigning";
    }
    VariableInfo *variableInfo = dynamic_cast<VariableInfo *>(symbolInfo.get());
    if (!variableInfo)
    {
        throw identifier + " is not a variable ( check if its a function )";
    }
    variableInfo->valueContainer = data;
}

void ContextHandler::addClass(const std::string &name, const classTypeInfo &info)
{
    Context &context = getInstance().getContext();
    context.addClass(name, info);
}

void ContextHandler::addClass(const std::string &name, classTypeInfo &&info)
{
    Context &context = getInstance().getContext();
    context.addClass(name, std::move(info));
}