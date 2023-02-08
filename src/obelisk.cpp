#include "knowledge_base.h"
#include "lexer.h"
#include "obelisk.h"
#include "parser.h"
#include "version.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>

static int obelisk::mainLoop()
{
    auto parser = std::unique_ptr<obelisk::Parser> {new obelisk::Parser()};
    std::unique_ptr<obelisk::KnowledgeBase> kb;

    try
    {
        kb = std::unique_ptr<obelisk::KnowledgeBase> {new obelisk::KnowledgeBase("cromer.kb")};
    }
    catch (obelisk::KnowledgeBaseException& exception)
    {
        std::cout << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Prime the first token.
    fprintf(stderr, "ready> ");
    try
    {
        parser->getNextToken();
    }
    catch (obelisk::LexerException& exception)
    {
        std::cout << "Error: " << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    while (true)
    {
        fprintf(stderr, "ready> ");
        switch (parser->getCurrentToken())
        {
            case obelisk::Lexer::kTokenEof :
                return EXIT_SUCCESS;
            case ';' : // ignore top-level semicolons.
                std::cout << "Identifier: " << parser->getLexer()->getIdentifier() << std::endl;
                std::cout << "Num: " << parser->getLexer()->getNumberValue() << std::endl;
                try
                {
                    parser->getNextToken();
                }
                catch (obelisk::LexerException& exception)
                {
                    std::cout << "Error: " << exception.what() << std::endl;
                    return EXIT_FAILURE;
                }
                break;
            case obelisk::Lexer::kTokenFact :
                parser->handleFact(kb);
                break;
            case obelisk::Lexer::kTokenRule :
                // parser->handleRule();
                break;
            case obelisk::Lexer::kTokenAction :
                // parser->handleAction();
                break;
            default :
                parser->getNextToken();
                break;
        }
    }

    return EXIT_SUCCESS;
}

void obelisk::showUsage()
{
    std::cout << obelisk::usageMessage << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<std::string> sourceFiles;
    std::string kbFile = "obelisk.kb";

    while (true)
    {
        int option_index = 0;
        switch (getopt_long(argc, argv, "k:hv", obelisk::long_options, &option_index))
        {
            case 'k' :
                kbFile = std::string(optarg);
                continue;
            case 'h' :
                obelisk::showUsage();
                return EXIT_SUCCESS;
                break;
            case 'v' :
                std::cout << "obelisk " << obelisk::version << std::endl;
                return EXIT_SUCCESS;
                break;
            default :
                obelisk::showUsage();
                return EXIT_FAILURE;
                break;

            case -1 :
                break;
        }

        break;
    }

    if (optind < argc)
    {
        while (optind < argc)
        {
            sourceFiles.push_back(argv[optind++]);
        }
    }

    if (sourceFiles.size() == 0)
    {
        obelisk::showUsage();
        return EXIT_FAILURE;
    }

    std::cout << sourceFiles[0] << std::endl;
    std::cout << kbFile << std::endl;

    return 0;

    return obelisk::mainLoop();
}
