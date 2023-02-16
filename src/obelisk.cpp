#include "knowledge_base.h"
#include "lexer.h"
#include "lib/include/obelisk.h"
#include "lib/version.h"
#include "obelisk.h"
#include "parser.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>

int obelisk::mainLoop(const std::vector<std::string>& sourceFiles, const std::string& kbFile)
{
    std::unique_ptr<obelisk::KnowledgeBase> kb;

    try
    {
        kb = std::unique_ptr<obelisk::KnowledgeBase> {new obelisk::KnowledgeBase(kbFile.c_str())};
    }
    catch (obelisk::KnowledgeBaseException& exception)
    {
        std::cout << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    size_t file = 0;
    std::shared_ptr<obelisk::Lexer> lexer;
    try
    {
        lexer = std::shared_ptr<obelisk::Lexer> {new obelisk::Lexer(sourceFiles[file++])};
    }
    catch (obelisk::LexerException& exception)
    {
        std::cout << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
    auto parser = std::unique_ptr<obelisk::Parser> {new obelisk::Parser(lexer)};

    // prime the first token
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
        switch (parser->getCurrentToken())
        {
            case obelisk::Lexer::kTokenEof :
                // end of source file found, create a new lexer and pass it to the parser to use
                if (file >= sourceFiles.size())
                {
                    return EXIT_SUCCESS;
                }
                try
                {
                    lexer = std::shared_ptr<obelisk::Lexer> {new obelisk::Lexer(sourceFiles[file++])};
                    parser->setLexer(lexer);
                    // prime the first token in the parser
                    parser->getNextToken();
                }
                catch (obelisk::LexerException& exception)
                {
                    std::cout << exception.what() << std::endl;
                    return EXIT_FAILURE;
                }
                break;
            case ';' :
                // semicolon found, the end of a statement
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
                parser->handleAction(kb);
                break;
            default :
                parser->getNextToken();
                break;
        }
    }

    return EXIT_SUCCESS;
}

static void obelisk::showUsage()
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

    return obelisk::mainLoop(sourceFiles, kbFile);
}
