#include <base/nodes.hpp>
#include <context/context_handler.hpp>
#include <enums/scope_type_enum.hpp>
#include <expressions/nodes.hpp>
#include <context/object.hpp>

ReturnStatementNode::ReturnStatementNode() : expressionNode(NULL) {}

ReturnStatementNode::ReturnStatementNode(ExpressionNode *const &expression)
    : expressionNode(expression) {}

std::vector<std::string> ReturnStatementNode::generateCode()
{
    return {};
}
bool ReturnStatementNode::analyze()
{
    return true;
}
void ReturnStatementNode::run()
{
    if (expressionNode)
        expressionNode->run();
    std::unique_ptr<Context> &context = ContextHandler::getContext(SCOPE_TYPE::FUNCTION_SCOPE);
    if (!context)
    {
        throw "return statement could only be used inside a function";
    }
    FunctionCallNode *function = dynamic_cast<FunctionCallNode *>(context->node);
    // look for the issue of changing node type while copying
    if (!function)
    {
        throw "only function call is allowed to create a function scope";
    }

    if (expressionNode)
    {
        if (getTypeString(function->typeNode.type) != getTypeString(expressionNode->valueNode.type))
        {
            throw "return type of function doesn't match the returned type";
        }
        function->valueNode.assignValue(expressionNode->valueNode.value);
    }
    else
    {
        if (getTypeString(function->typeNode.type) != VOID_TYPE)
        {
            throw "return type of function doesn't match the returned type";
        }
        function->valueNode.type = VOID_TYPE;
    }

    ContextHandler::returnTillContext(SCOPE_TYPE::FUNCTION_SCOPE);
}

void ReturnStatementNode::print(std::string prefix)
{
    std::cout << prefix << "Return Node" << std::endl;
    prefix += "\t-> ";
    if (expressionNode)
        expressionNode->print(prefix);
}