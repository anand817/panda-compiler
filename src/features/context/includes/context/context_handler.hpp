#ifndef CONTEXT_HANDLER_H
#define CONTEXT_HANDLER_H

#include <context.hpp>
#include <stack>

// singleton class that handles context in the programme
class ContextHandler
{
    std::stack<Context> contextStack;
    int contextCounter;

private:
    ContextHandler();
    ContextHandler(ContextHandler &&other) = delete;
    ContextHandler(const ContextHandler &other) = delete;

public:
    ContextHandler &getInstance();

public:
    void addContext();
    void removeContext();
    Context &getContext();
};

#endif // CONTEXT_HANDLER_H