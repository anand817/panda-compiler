#include <context/context_handler.hpp>

ContextHandler::ContextHandler() : contextCounter(0), contextStack(), poppedContextStack() {}

ContextHandler &ContextHandler::getInstance()
{
    static ContextHandler instance;
    return instance;
}

std::unique_ptr<Context> &ContextHandler::pushContextImpl(SCOPE_TYPE scope_type, Node *const &node)
{
    std::unique_ptr<Context> &context = contextStack.emplace_back(std::make_unique<Context>(contextCounter, scope_type, node));
    contextCounter += 1;
    return context;
}

std::unique_ptr<Context> &ContextHandler::pushContext(SCOPE_TYPE scope_type, Node *const &node)
{
    ContextHandler &instance = getInstance();
    auto &context = instance.pushContextImpl(scope_type, node);
    return context;
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
        if ((*it)->symbolTable.find(identifier) != (*it)->symbolTable.end())
        {
            return (*it)->symbolTable[identifier];
        }
    }

    return not_found;
}

std::unique_ptr<SymbolInfo> &ContextHandler::findSymbol(const std::string &identifier)
{
    ContextHandler &instance = getInstance();
    return instance.findSymbolImpl(identifier);
}

std::unique_ptr<Context> &ContextHandler::getContext(SCOPE_TYPE scope)
{
    static std::unique_ptr<Context> not_found(nullptr);
    ContextHandler &instance = getInstance();
    auto &contextStack = instance.contextStack;

    for (auto it = contextStack.rbegin(); it != contextStack.rend(); it++)
    {
        if ((*it)->scope_type == scope)
            return *it;
    }
    return not_found;
}

std::unique_ptr<Context> &ContextHandler::getContext()
{
    return contextStack.back();
}

std::unique_ptr<ClassInfo> &ContextHandler::findClassImpl(const std::string &name)
{
    static std::unique_ptr<ClassInfo> not_found;

    // iterate in reverse direction to get the closest symbol reference
    for (auto it = contextStack.rbegin(); it != contextStack.rend(); it++)
    {
        if ((*it)->classTable.find(name) != (*it)->classTable.end())
        {
            return (*it)->classTable[name];
        }
    }

    return not_found;
}

std::unique_ptr<ClassInfo> &ContextHandler::findClass(const std::string &name)
{
    ContextHandler &instance = getInstance();
    return instance.findClassImpl(name);
}

void ContextHandler::printTableImpl()
{
    for (auto &context : poppedContextStack)
    {
        context->print();
    }
}

void ContextHandler::printTable()
{
    ContextHandler &instance = getInstance();
    instance.printTableImpl();
}

void ContextHandler::printClassTableImpl()
{
    for (auto &context : poppedContextStack)
    {
        context->printClassTable();
    }
}

void ContextHandler::addSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data)
{
    std::unique_ptr<Context> &context = getInstance().getContext();
    context->addSymbol(identifier, dataType, data);
}

void ContextHandler::addSymbol(const std::string &identifier, const typeInfo &dataType, const std::vector<std::pair<std::string, typeInfo>> &parameterList, BlockNode *const &functionBlockNode)
{
    std::unique_ptr<Context> &context = getInstance().getContext();
    context->addSymbol(identifier, dataType, parameterList, functionBlockNode);
}

void ContextHandler::updateSymbol(const std::string &identifier, const typeInfo &dataType, const valueType &data)
{
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

void ContextHandler::returnTillContext(SCOPE_TYPE scope)
{
    ContextHandler &instance = getInstance();
    auto &contextStack = instance.contextStack;

    for (auto it = contextStack.rbegin(); it != contextStack.rend(); it++)
    {
        if ((*it)->scope_type == scope)
        {
            for (auto iter = it.base() - 1; iter != contextStack.end(); iter++)
            {
                (*iter)->stop_processing = true;
            }
            return;
        }
    }

    throw "no context found with specified type";
}

void ContextHandler::addClass(const std::string &name, const ClassTypeInfo &info)
{
    std::unique_ptr<Context> &context = getInstance().getContext();
    context->addClass(name, info);
}

void ContextHandler::addClass(const std::string &name, ClassTypeInfo &&info)
{
    std::unique_ptr<Context> &context = getInstance().getContext();
    context->addClass(name, std::move(info));
}

void ContextHandler::printClassTable()
{
    auto &instance = getInstance();
    instance.printClassTableImpl();
}