#include "lexer.h"

#include <iostream>

obelisk::Lexer::Lexer(const std::string& sourceFile)
{
    fileStream_.open(sourceFile, std::ifstream::in);
    if (!fileStream_)
    {
        throw obelisk::LexerException("could not open source file " + sourceFile);
    }
}

obelisk::Lexer::~Lexer()
{
    fileStream_.close();
    fileStream_.clear();
}

int obelisk::Lexer::getToken()
{
    while (isspace(lastChar))
    {
        lastChar = fileStream_.get();
    }

    if (isalpha(lastChar))
    {
        eraseIdentifier();
        appendIdentifier(lastChar);
        while (isalnum((lastChar = fileStream_.get())))
        {
            appendIdentifier(lastChar);
        }

        if (getIdentifier() == "fact")
        {
            return Token::kTokenFact;
        }

        if (getIdentifier() == "rule")
        {
            return Token::kTokenFact;
        }

        if (getIdentifier() == "action")
        {
            return Token::kTokenAction;
        }

        if (getIdentifier() == "def")
        {
            return Token::kTokenDef;
        }

        if (getIdentifier() == "extern")
        {
            return kTokenExtern;
        }

        return kTokenIdentifier;
    }

    if (isdigit(lastChar))
    {
        bool firstPeriod = false;
        std::string numberStr;
        do
        {
            if (firstPeriod && lastChar == '.')
            {
                throw obelisk::LexerException("invalid double value");
            }
            else if (!firstPeriod && lastChar == '.')
            {
                firstPeriod = true;
            }
            numberStr += lastChar;
            lastChar = fileStream_.get();
        }
        while (isdigit(lastChar) || lastChar == '.');

        setNumberValue(strtod(numberStr.c_str(), nullptr));

        return kTokenNumber;
    }

    if (lastChar == '#')
    {
        commentLine(&lastChar);

        if (lastChar != EOF)
        {
            return getToken();
        }
    }
    else if (lastChar == '/')
    {
        lastChar = fileStream_.get();
        if (lastChar == '/')
        {
            commentLine(&lastChar);

            if (lastChar != EOF)
            {
                return getToken();
            }
        }
    }

    if (lastChar == EOF)
    {
        return kTokenEof;
    }

    int thisChar = lastChar;
    lastChar     = fileStream_.get();
    return thisChar;
}

void obelisk::Lexer::commentLine(int* lastChar)
{
    do
    {
        *lastChar = fileStream_.get();
    }
    while (*lastChar != EOF && *lastChar != '\n' && *lastChar != '\r');
}

const std::string& obelisk::Lexer::getIdentifier()
{
    return identifier_;
}

void obelisk::Lexer::setIdentifier(const std::string& identifier)
{
    identifier_ = identifier;
}

void obelisk::Lexer::eraseIdentifier()
{
    identifier_ = "";
}

void obelisk::Lexer::appendIdentifier(int lastChar)
{
    identifier_ += lastChar;
}

double obelisk::Lexer::getNumberValue()
{
    return numberValue_;
}

void obelisk::Lexer::setNumberValue(double numberValue)
{
    numberValue_ = numberValue;
}
