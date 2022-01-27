#ifndef TOKENS_H
#define TOKENS_H

#include <string>

namespace Tokens {
    enum TokenType {
        BYTE,
        NUMBER,
        SYMBOL,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        POWER,
        TRUE,
        FALSE,
        NIL,
        SEMICOLON,
        EOF_
    };

    class Token {
        public:
            int line;
            TokenType type;
            signed char byte;
            double value;
            std::string symbol;

            Token(int, TokenType, signed char);
            Token(int, TokenType, double = 0);
            Token(int, TokenType, std::string);

            std::string to_string();
    };
};

#endif // TOKENS_H