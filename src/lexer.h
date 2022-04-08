#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <map>
#include <regex>

#include "token.h"
#include "location.h"

namespace pluto
{
    std::map<std::string, TokenType> regexes{
        {"^[0-9]+(?![0-9.])", TokenType::INT},
        {"^[0-9]+\\.[0-9]+", TokenType::DOUBLE},
        {"^\"[^\"]*\"", TokenType::STRING},
        {"^\\s+", TokenType::IGNORE}
    };

    // Lexer - Converts the source code into a stream of tokens.

    class Lexer
    {
    private:
        std::string text{};
        Location loc;
        char current_char;

    public:
        Lexer(const std::string &text);
        void raise_error(const std::string &msg) const;
        void advance(int amount = 1);
        Token next();
    };
} // namespace pluto

#endif // LEXER_H