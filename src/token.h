#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace pluto
{
    enum TokenType
    {
        STRING,
        NUMBER,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        EOF_
    };

    class Token
    {
        public:
            int line;
            TokenType type;
            std::string string_val;
            double num_val;

            Token(int line, TokenType type);
            Token(int line, TokenType type, std::string string_val);
            Token(int line, TokenType type, double num_val);

            std::string to_string();
    };
}

#endif