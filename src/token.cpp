#include <string>
#include <cstdint>

#include "token.h"

namespace pluto
{
    Token::Token(int line, TokenType type)
    {
        this->line = line;
        this->type = type;
    }

    Token::Token(int line, TokenType type, std::int32_t int_val)
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

    Token::Token(int line, TokenType type, std::string string_val, bool is_name)
    {
        this->line = line;
        this->type = type;

        if (is_name)
        {
            this->name = string_val;
        }
        else
        {
            this->string_val = string_val;
        }
    }

    std::string Token::to_string()
    {
        switch (type)
        {
        case INT:
            return "INT:" + std::to_string(int_val);
        case DOUBLE:
            return "DOUBLE:" + std::to_string(double_val);
        case STRING:
            return "STRING:" + string_val;
        case NAME:
            return "NAME:" + name;
        case TRUE:
            return "TRUE";
        case FALSE:
            return "FALSE";
        case NIL:
            return "NIL";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case MULTIPLY:
            return "MULTIPLY";
        case DIVIDE:
            return "DIVIDE";
        case MOD:
            return "MOD";
        case OR:
            return "OR";
        case AND:
            return "AND";
        case XOR:
            return "XOR";
        case NOT:
            return "NOT";
        case BOR:
            return "BOR";
        case BAND:
            return "BAND";
        case BXOR:
            return "BXOR";
        case BNOT:
            return "BNOT";
        case LSHIFT:
            return "LSHIFT";
        case RSHIFT:
            return "RSHIFT";
        case LT:
            return "LT";
        case GT:
            return "GT";
        case LTE:
            return "LTE";
        case GTE:
            return "GTE";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case SEMICOLON:
            return "SEMICOLON";
        case EOF_:
            return "EOF";
        default:
            return "UNKNOWN";
        }
    }
}