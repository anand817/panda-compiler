#ifndef BASE_NODES_H
#define BASE_NODES_H

#include <vector>
#include <string>

class Node
{
public:
    virtual std::vector<std::string> generateCode() = 0;
    virtual void run() = 0;
};

class StatementNode : public Node
{
};

class ProgrammeNode : public Node
{
    std::vector<StatementNode *> statements;

public:
    ProgrammeNode();

    virtual std::vector<std::string> generateCode();
    virtual void run();
};

#endif // BASE_NODES_H
