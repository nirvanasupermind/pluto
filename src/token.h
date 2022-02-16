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
        NAME,
        TRUE,
        FALSE,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MOD,
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
        std::string name;

        Token(int line, TokenType type);
        Token(int line, TokenType type, int int_val);
        Token(int line, TokenType type, double double_val);
        Token(int line, TokenType type, std::string string_val, bool is_name = false);

        std::string to_string();
    };
}

#endif