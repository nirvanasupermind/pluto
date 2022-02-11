#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "token.h"

namespace pluto
{
    class Lexer
    {
    public:
        std::string filename;
        std::string text;
        int idx;
        int ln;

        Lexer(std::string filename, std::string text);

        std::vector<Token> generate_tokens();

        Token generate_number();
    };
}

#endif