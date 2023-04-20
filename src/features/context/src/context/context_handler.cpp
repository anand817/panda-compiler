#include <context/context_handler.hpp>

ContextHandler::ContextHandler() : contextCounter(0), contextStack({}) {}

ContextHandler &ContextHandler::getInstance()
{
    static ContextHandler instance;
    return instance;
}

void ContextHandler::pushContext()
{
    contextStack.emplace_back(contextCounter);
    contextCounter += 1;
}

void ContextHandler::popContext()
{
    contextStack.pop_back();
}

Context &ContextHandler::getContext()
{
    return contextStack.back();
}