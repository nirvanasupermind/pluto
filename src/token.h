#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace pluto
{
    enum TokenType
    {
        INT,
        DOUBLE,
        STRING,
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
            int int_val;
            double double_val;
            std::string string_val;

            Token(int line, TokenType type);
            Token(int line, TokenType type, int int_val);
            Token(int line, TokenType type, double double_val);
            Token(int line, TokenType type, std::string string_val);

            std::string to_string();
    };
}

#endif