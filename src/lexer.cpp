#include "lexer.h"

#include <iostream>

int obelisk::Lexer::getToken()
{
    static int lastChar = ' ';

    while (isspace(lastChar))
    {
        lastChar = std::getc(stdin);
    }

    if (isalpha(lastChar))
    {
        eraseIdentifier();
        appendIdentifier(lastChar);
        while (isalnum((lastChar = getchar())))
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

    if (isdigit(lastChar) || lastChar == '.')
    {
        std::string numberStr;
        do
        {
            numberStr += lastChar;
            lastChar = getchar();
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
        lastChar = getchar();
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
    lastChar     = getchar();
    return thisChar;
}

void obelisk::Lexer::commentLine(int* lastChar)
{
    do
    {
        *lastChar = getchar();
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
