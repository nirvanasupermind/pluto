#include <string>

#include "location.h"
#include "token.h"

namespace pluto
{
    Token::Token()
        : loc(Location(0,0,0)), type(), lexeme() {}

    Token::Token(const Location &loc, const TokenType &type, const std::string &lexeme)
        : loc(loc), type(type), lexeme(lexeme)
    {
    }

    std::string Token::str() const
    {
        std::string result;

        switch(type) {
            case TokenType::INT:
                result += "INT";
                break;
            case TokenType::DOUBLE:
                result += "DOUBLE";
                break;
            case TokenType::STRING:
                result += "STRING";
                break;
            case TokenType::IGNORE:
                result += "IGNORE";
                break;
            case TokenType::EOF_:
                result += "EOF";
                break;
        }   

        result += ":" + lexeme;

        return result;
    }
} // namespace pluto