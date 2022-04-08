#ifndef LEXER_H
#define LEXER_H

#include "location.h"
#include "token.h"

namespace pluto
{
    const std::string WHITESPACE = " \t";
    const std::string NEWLINE = "\n\r";

    // Lexer - Converts the source code into a stream of tokens

    class Lexer
    {
    public:
        std::string text{};
        Location loc;
        char current;

        Lexer(const std::string &text);

        void advance();
        Token gettok();
    };
}

#endif