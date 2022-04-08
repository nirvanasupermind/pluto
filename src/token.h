#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "location.h"

namespace pluto
{
    // Token - String in the program with an assigned type or meaning

    enum class TokenType
    {
        INT,
        DOUBLE,
        SYMBOL,
        EOF_
    };

    class Token
    {
    public:
        Location loc;
        TokenType type;
        std::string lexeme;

        Token(const Location &loc, const TokenType &type, const std::string &lexeme);

        bool matches(const TokenType &type, const std::string &lexeme) const;
        std::string repr() const;
    };

} // namespace pluto

#endif // TOKEN_H