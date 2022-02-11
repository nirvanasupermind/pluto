#include <string>

#include "token.h"

namespace pluto
{
    Token::Token(int line, TokenType type)
    {
        this->line = line;
        this->type = type;
    }

    Token::Token(int line, TokenType type, int int_val)
    {
        this->line = line;
        this->type = type;
        this->int_val = int_val;
    }

    Token::Token(int line, TokenType type, double double_val)
    {
        this->line = line;
        this->type = type;
        this->double_val = double_val;
    }

    Token::Token(int line, TokenType type, std::string string_val)
    {
        this->line = line;
        this->type = type;
        this->string_val = string_val;
    }

    std::string Token::to_string()
    {
        switch (type)
        {
        case INT:
            return "INT:"+std::to_string(int_val);
        case DOUBLE:
            return "DOUBLE:"+std::to_string(double_val);
        case STRING:
            return "STRING:"+string_val;
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
