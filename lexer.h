#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "tokens.h"

namespace pluto
{

    const std::string WHITESPACE = " \n\t";
    const std::string DIGITS = "0123456789";

    class Lexer
    {
    public:
        std::string text{};
        std::size_t pos;
        char current;

        Lexer(const std::string &text);

        void advance();
        std::vector<Token> generate_tokens();
        Token generate_number();
    };

} // namespace pluto

#endif 