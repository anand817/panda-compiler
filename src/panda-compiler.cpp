#include <parser.hpp>
#include <cstring>

extern int yyparse();
extern FILE *yyin;
extern StatementList *programmeRoot;

std::string inputFilename, outputFileName, symbolTableFileName;

void parseArguments(int argc, char *argv[])
{
    while (++argv, --argc)
    {
        if (**argv == '-')
        {
            if (strcmp(*argv, "-o") == 0 || strcmp(*argv, "--output") == 0)
            {
                if (--argc < 1)
                {
                    std::cerr << "error: missing output filename!\n\n";
                }

                outputFileName = std::string(*(++argv));
            }
            else if (strcmp(*argv, "-s") == 0 || strcmp(*argv, "--sym_table") == 0)
            {
                if (--argc < 1)
                {
                    std::cerr << "error: missing symbol table filename!\n\n";
                }

                symbolTableFileName = string(*(++argv));
            }
            else if (strcmp(*argv, "-i") == 0 || strcmp(*argv, "--input") == 0)
            {
                if (--argc < 1)
                {
                    std::cerr << "error: missing input filename!\n\n";
                }

                symbolTableFileName = string(*(++argv));
            }
            else
            {
                std::cerr << "unknown argument " << *argv << " !\n\n";
            }
        }
        else if (inputFilename.empty())
        {
            inputFilename = string(*argv);
        }
        else
        {
            std::cerr << "warning: too many arguments " << *argv << " ignored!\n";
        }
    }

    if (inputFilename.empty())
    {
        std::cerr << "error: missing input filename argument!\n\n";
    }
}

int main(int argc, char *argv[])
{
    parseArguments(argc, argv);

    if (inputFilename.empty())
    {
        return 0;
    }

    yyin = fopen(inputFilename.c_str(), "r");

    if (yyin == NULL)
    {
        std::cerr << "error: could not open the input file" << inputFilename << "!\n";
        return 0;
    }

    yyparse();

    if (programmeRoot)
    {

        try
        {

            for (auto statement : *programmeRoot)
            {
                statement->print("");
            }

            ContextHandler::pushContext(SCOPE_TYPE::BLOCK_SCOPE, new BlockNode(*programmeRoot));
            for (auto statement : *programmeRoot)
            {
                statement->run();
            }
            ContextHandler::popContext();

            // for (auto statement : *programmeRoot)
            // {
            //     statement->print("");
            // }
        }
        catch (const char *e)
        {
            std::cout << "Error: " << e << std::endl;
        }
        catch (std::string e)
        {
            std::cout << "Error: " << e << std::endl;
        }

        // std::cout << "\n\n------------ Symbol table -----------------\n\n";

        // ContextHandler::printTable();
        ContextHandler::printClassTable();
    }

    fclose(yyin);

    if (programmeRoot != NULL)
    {
        delete programmeRoot;
    }

    return 0;
}