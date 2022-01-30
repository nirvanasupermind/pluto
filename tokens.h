#ifndef TOKENS_H
#define TOKENS_H

#include <string>

namespace Tokens {
    enum TokenType {
        BYTE,
        NUMBER,
        TRUE,
        FALSE,
        NIL,
        VAR,
        IF,
        ELSE,
        WHILE,
        SYMBOL,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        LCURLY,
        RCURLY,
        POWER,
        LT,
        GT,
        LE,
        GE,
        EE,
        NE,
        EQ,
        NOT,
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