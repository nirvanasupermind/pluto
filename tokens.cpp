#include <iostream>
#include <string>

#include "tokens.h"

namespace Tokens {
    Token::Token(int line, TokenType type, signed char byte) {
        this->line = line;
        this->type = type;
        this->byte = byte;
    }

    Token::Token(int line, TokenType type, double value) {
        this->line = line;
        this->type = type;
        this->value = value;
    }

    Token::Token(int line, TokenType type, std::string symbol) {
        this->line = line;
        this->type = type;
        this->symbol = symbol;
    }

    std::string Token::to_string() {
        std::string s;

        switch (type) {
            case BYTE: s += "BYTE"; break;
            case NUMBER: s += "NUMBER"; break;
            case TRUE: s += "TRUE"; break;
            case FALSE: s += "FALSE"; break;
            case NIL: s += "NIL"; break;
            case VAR: s += "VAR"; break;
            case IF: s += "IF"; break;
            case ELSE: s += "ELSE"; break;
            case FOR: s += "FOR"; break;
            case WHILE: s += "WHILE"; break;
            case SYMBOL: s += "SYMBOL"; break;
            case PLUS: s += "PLUS"; break;
            case MINUS: s += "MINUS"; break;
            case MULTIPLY: s += "MULTIPLY"; break;
            case DIVIDE: s += "DIVIDE"; break;
            case LPAREN: s += "LPAREN"; break;
            case RPAREN: s += "RPAREN"; break;
            case LCURLY: s += "LCURLY"; break;
            case RCURLY: s += "RCURLY"; break;
            case POWER: s += "POWER"; break;
            case LT: s += "LT"; break;
            case GT: s += "GT"; break;
            case LE: s += "LE"; break;
            case GE: s += "GE"; break;
            case EE: s += "EE"; break;
            case NE: s += "NE"; break;
            case EQ: s += "EQ"; break;
            case OR: s += "OR"; break;
            case AND: s += "AND"; break;
            case XOR: s += "XOR"; break;
            case NOT: s += "NOT"; break;
            case BITOR: s += "OR"; break;
            case BITAND: s += "AND"; break;
            case BITXOR: s += "XOR"; break;
            case BITNOT: s += "NOT"; break;
            case LSHIFT: s += "LSHIFT"; break;
            case RSHIFT: s += "LSHIFT"; break;
            case SEMICOLON: s += "SEMICOLON"; break;
            case EOF_: s += "EOF"; break;
        }

        if (type == NUMBER)
            s += ":" + std::to_string(value);

        return s;
    }

    // void print_token(Token& token, bool newline) {
    //     std::cout << static_cast<std::string>(token);

    //     if (newline) std::cout << '\n';
    // }
};