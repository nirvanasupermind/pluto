#ifndef TOKENS_H
#define TOKENS_H

#include <string>

namespace Tokens {
    enum TokenType {
        BYTE,
        NUMBER,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        POWER,
        SEMICOLON,
        EOF_
    };

    class Token {
        public:
            int line;
            TokenType type;
            signed char byte;
            double value;

            Token(int, TokenType, signed char);
            Token(int, TokenType, double = 0);

            std::string to_string();
    };
};

#endif // TOKENS_H