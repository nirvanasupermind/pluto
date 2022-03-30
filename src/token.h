#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <cstdint>

namespace pluto
{
    enum TokenType
    {
        INT,
        DOUBLE,
        CHAR,
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
        DEF,
        RETURN,
        LAMBDA,
        CLASS,
        MODULE,
        INCLUDE,
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
        COMMA,
        DOT,
        SEMICOLON,
        LPAREN,
        RPAREN,
        LBRACKET,
        RBRACKET,
        LCURLY,
        RCURLY,
        EOF_
    };

    class Token
    {
    public:
        int line;
        TokenType type;
        union
        {
            std::int32_t int_val;
            double double_val;
            unsigned char char_val;
        };
        std::string string_val;
        std::string name;

        Token(int line, TokenType type);
        Token(int line, TokenType type, unsigned char char_val);
        Token(int line, TokenType type, std::int32_t int_val);
        Token(int line, TokenType type, double double_val);
        Token(int line, TokenType type, std::string string_val, bool is_name = false);

        std::string str();
    };
}

#endif