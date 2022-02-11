#include <string>

#include "token.h"

namespace pluto
{
    Token::Token(int line, TokenType type)
    {
        this->line = line;
        this->type = type;
    }

    Token::Token(int line, TokenType type, std::string string_val)
    {
        this->line = line;
        this->type = type;
        this->string_val = string_val;
    }

    Token::Token(int line, TokenType type, double num_val)
    {
        this->line = line;
        this->type = type;
        this->num_val = num_val;
    }

    std::string Token::to_string()
    {
        switch (type)
        {
        case STRING:
            return "STRING";
        case NUMBER:
            return "NUMBER";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case MULTIPLY:
            return "MULTIPLY";
        case DIVIDE:
            return "DIVIDE";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case EOF_:
            return "EOF";
        default:
            return "UNKNOWN";
        }
    }
}
