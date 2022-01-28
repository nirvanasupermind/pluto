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
            case SYMBOL: s += "SYMBOL"; break;
            case PLUS: s += "PLUS"; break;
            case MINUS: s += "MINUS"; break;
            case MULTIPLY: s += "MULTIPLY"; break;
            case DIVIDE: s += "DIVIDE"; break;
            case LPAREN: s += "LPAREN"; break;
            case RPAREN: s += "RPAREN"; break;
            case POWER: s += "POWER"; break;
            case EQ: s += "EQ"; break;
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