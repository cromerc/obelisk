#include "lexer.h"
#include "obelisk.h"
#include "parser.h"

#include <iostream>

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

    mainLoop();

    return EXIT_SUCCESS;
}
