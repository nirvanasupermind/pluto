#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <map>

#include "token.h"

namespace pluto
{
    const std::string WHITESPACE(" \n\t");
    std::map<char, char> escape {{'b', '\b'}, {'f', '\f'}, {'n', '\n'}, {'r', '\r'}, {'t', '\t'}};

    class Lexer
    {
    public:
        std::string filename;
        std::string text;
        std::size_t pos;
        int line;

        Lexer(std::string filename, std::string text);

        void raise_error(std::string msg);

        void advance();

        char current_char();

        std::vector<Token> generate_tokens();

        Token generate_number();

        Token generate_string();
        
        Token generate_name();
    };
}

#endif