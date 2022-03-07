#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace pluto
{
    enum TokenType
    {
        BYTE,
        INT,
        DOUBLE,
        STRING,
        NAME,
        TRUE,
        FALSE,
        NIL,
        VAR,
        CONST,
        IF,
        ELSE,
        FOR,
        WHILE,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MOD,
        OR,
        AND,
        XOR,
        NOT,
        BOR,
        BAND,
        BXOR,
        BNOT,
        LSHIFT,
        RSHIFT,
        EQ,
        EE,
        NE,
        LT,
        GT,
        LTE,
        GTE,
        SEMICOLON,
        LPAREN,
        RPAREN,
        LCURLY,
        RCURLY,
        EOF_
    };

    class Token
    {
    public:
        int line;
        TokenType type;
        signed char byte_val;
        long int int_val;
        double double_val;
        std::string string_val;
        std::string name;

        Token(int line, TokenType type);
            Token(int line, TokenType type, signed char byte_val);
        Token(int line, TokenType type, long int int_val);
        Token(int line, TokenType type, double double_val);
        Token(int line, TokenType type, std::string string_val, bool is_name = false);

        std::string to_string();
    };
}

#endif