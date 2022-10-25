#include "knowledge_base.h"
#include "lexer.h"
#include "obelisk.h"
#include "parser.h"

#include <iomanip>
#include <iostream>
#include <limits>

static void mainLoop()
{
    obelisk::Parser* parser = new obelisk::Parser();

    // Prime the first token.
    fprintf(stderr, "ready> ");
    parser->getNextToken();

    while (true)
    {
        fprintf(stderr, "ready> ");
        switch (parser->getCurrentToken())
        {
            case obelisk::Lexer::kTokenEof :
                return;
            case obelisk::Lexer::kTokenInvalid :
                std::cerr << "Invalid token!\n";
                parser->getNextToken();
                return;
            case ';' : // ignore top-level semicolons.
                std::cout << "Identifier: "
                          << parser->getLexer()->getIdentifier() << std::endl;
                std::cout << "Num: " << parser->getLexer()->getNumberValue()
                          << std::endl;
                parser->getNextToken();
                break;
            default :
                parser->getNextToken();
                break;
        }
    }
}

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    try
    {
        obelisk::KnowledgeBase* kb = new obelisk::KnowledgeBase("cromer.kb");

        /*std::vector<std::string> leftObjects;
        std::vector<std::string> rightObjects;
        leftObjects.push_back("chris");
        leftObjects.push_back("martin");

        rightObjects.push_back("happy");
        rightObjects.push_back("smart");

        kb->addFacts("is", leftObjects, rightObjects);*/
    }
    catch (obelisk::KnowledgeBaseException& exception)
    {
        std::cout << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    // This can be used to store a double as 2 floats in the database, then restore it back to a double.
    // Inspired by Godot's double precision on the GPU to render large worlds.
    /*float first;
    float second;
    double var = 0.123456789012345;
    kb->getFloat(&first, &second, var);
    std::cout << std::setprecision(std::numeric_limits<double>::digits10)
              << "Double: " << var << std::endl
              << "First: " << first << std::endl
              << "Second: " << second << std::endl;
    var = 0.0;
    kb->getDouble(&var, first, second);
    std::cout << std::setprecision(std::numeric_limits<double>::digits10)
              << "Double: " << var << std::endl
              << "First: " << first << std::endl
              << "Second: " << second << std::endl;*/

    mainLoop();

    return EXIT_SUCCESS;
}
