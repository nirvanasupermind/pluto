#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace pluto
{
    enum class TokenType
    {
        NUMBER,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN
    };

    class Token
    {
        public:
            int ln;
            TokenType type;
            double num_val;

            Token(int ln, TokenType type);
            Token(int ln, TokenType type, double num_val);
    };
}

#endif