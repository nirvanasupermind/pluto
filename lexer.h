#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <cstddef>

#define WHITESPACE std::string(" \n\t")
#define DIGITS std::string("0123456789")
#define NONDIGITS std::string("_abcdefghijklmnopqrstuvwxyz")

namespace Lexer {
    class Lexer {
        public:
            int line = 1;
            std::string filename;
            std::string text;
            std::size_t index;
            std::string current_char;

            Lexer(std::string, std::string);

            void advance();
            std::vector<Tokens::Token> get_tokens();
            Tokens::Token get_number();
            Tokens::Token get_name();
    };

    void print_tokens(std::vector<Tokens::Token>&);
}

#endif // LEXER_H