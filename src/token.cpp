#include <string>

#include "token.h"

namespace pluto
{
    Token::Token(const Location &loc, const TokenType &type, const std::string &lexeme)
        : loc(loc), type(type), lexeme(lexeme)
    {
    }

    bool Token::matches(const TokenType &type, const std::string &lexeme) const
    {
        return type == this->type && lexeme == this->lexeme;
    }

    std::string Token::repr() const
    {
        std::string result;

        switch (type)
        {
        case TokenType::INT:
            result += "INT";
            break;
        case TokenType::DOUBLE:
            result += "DOUBLE";
            break;
        case TokenType::SYMBOL:
            result += "SYMBOL";
            break;
        case TokenType::EOF_:
            result += "EOF";
            break;
        default:
            result += "UNKNOWN";
        }

        result += ":" + lexeme;

        return result;
    }

} // namespace pluto