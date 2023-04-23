#include <loop/nodes.hpp>
#include <expressions/nodes.hpp>
#include <context/context_handler.hpp>

ForNode::ForNode(StatementNode *const &initialzer, ExpressionNode *const &condition, ExpressionNode *const &updation, BlockNode *const &body)
    : initialize_statement(initialzer),
      condition_expression(condition),
      update_expression(updation),
      body(body) {}

ForNode::ForNode(const ForNode &other)
    : initialize_statement(other.initialize_statement),
      condition_expression(other.condition_expression),
      update_expression(other.update_expression),
      body(other.body) {}

ForNode::ForNode(ForNode &&other)
    : initialize_statement(std::move(other.initialize_statement)),
      condition_expression(std::move(other.condition_expression)),
      update_expression(std::move(other.update_expression)),
      body(std::move(other.body)) {}

ForNode &ForNode::operator=(const ForNode &other)
{
    if (this != &other)
    {
        initialize_statement = other.initialize_statement;
        condition_expression = other.condition_expression;
        update_expression = other.update_expression;
        body = other.body;
    }

    return *this;
}
ForNode &ForNode::operator=(ForNode &&other)
{
    if (this != &other)
    {
        initialize_statement = std::move(other.initialize_statement);
        condition_expression = std::move(other.condition_expression);
        update_expression = std::move(other.update_expression);
        body = std::move(other.body);
    }

    return *this;
}

std::vector<std::string> ForNode::generateCode()
{
    return {};
}
bool ForNode::analyze()
{
    return true;
}
void ForNode::run()
{
    ContextHandler::pushContext(SCOPE_TYPE::LOOP_SCOPE, this);
    bool stop_processing = false;
    if (initialize_statement)
        initialize_statement->run();

    if (condition_expression)
    {
        condition_expression->run();
        if (getTypeString(condition_expression->valueNode.type) != BOOL_TYPE)
        {
            throw "conditional expression should be boolean";
        }
    }

    if (body == nullptr)
    {
        throw "body of for statement can't be null";
    }

    while ((condition_expression == nullptr || std::get<bool>(condition_expression->valueNode.value)))
    {
        auto &context = ContextHandler::getContext(SCOPE_TYPE::LOOP_SCOPE);
        stop_processing = context->stop_processing;
        if (stop_processing)
            break;
        ContextHandler::pushContext(SCOPE_TYPE::LOOP_BLOCK_SCOPE, this);
        body->run(SCOPE_TYPE::LOOP_BLOCK_SCOPE);
        ContextHandler::popContext();
        if (update_expression)
            update_expression->run();
        if (condition_expression)
            condition_expression->run();
    }
    ContextHandler::popContext();
}

void ForNode::assignBody(BlockNode *const &body)
{
    this->body = body;
}

void ForNode::print(std::string prefix)
{
    std::cout << prefix << "For Node" << std::endl;
    prefix += "\t-> ";
    if (initialize_statement)
        initialize_statement->print(prefix);
    if (condition_expression)
        condition_expression->print(prefix);
    if (update_expression)
        update_expression->print(prefix);
    if (body)
        body->print(prefix);
}