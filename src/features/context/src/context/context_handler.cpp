#include <context_handler.hpp>

ContextHandler::ContextHandler()
{
    contextCounter = 0;
    while (!contextStack.empty())
    {
        contextStack.pop();
    }
}

ContextHandler &ContextHandler::getInstance()
{
    static ContextHandler instance;
    return instance;
}

void ContextHandler::addContext()
{
    if (contextCounter > 0)
    {
        // if there is a previous context variable then
        // append their symbol into new one
        Context &previousContext = this->getContext();
        contextStack.emplace(contextCounter, previousContext.symbolTable);
    }
    else
    {
        // when no previous context then add a empty symbol table
        contextStack.emplace(contextCounter);
    }
    contextCounter += 1;
}

void ContextHandler::removeContext()
{
    contextStack.pop();
}

Context &ContextHandler::getContext()
{
    return contextStack.top();
}