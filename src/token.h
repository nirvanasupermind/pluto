#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "location.h"

namespace pluto
{
    
    enum class TokenType
    {
        INT,
        DOUBLE,
        STRING,
        IGNORE,
        EOF_
    };

    // Token - String in the program with an assigned type or meaning,
    // such as a numeric or string literal.

    class Token
    {
    public:
        Location loc;
        TokenType type;
        std::string lexeme{};
        Token();
        Token(const Location &loc, const TokenType &type, const std::string &lexeme);
        std::string str() const;
    };

} // namespace pluto

#endif // TOKEN_H