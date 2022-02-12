#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "token.h"

namespace pluto
{
    const std::string WHITESPACE(" \n\t");

    class Lexer
    {
    public:
        std::string filename;
        std::string text;
        int position;
        int line;

        Lexer(std::string filename, std::string text);

        void error();

        void advance();

        char current_char();

        std::vector<Token> generate_tokens();

        Token generate_number();

        Token generate_string();
    };
}

#endif