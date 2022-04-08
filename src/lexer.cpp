#include <string>
#include <vector>
#include <map>
#include <regex>

#include "location.h"
#include "token.h"
#include "lexer.h"

namespace pluto
{
    Lexer::Lexer(const std::string &text)
        : text(text), loc(Location(-1, 1, 0)), current_char('\0')
    {
        advance();
    }

    void Lexer::raise_error(const std::string &msg) const
    {
        throw std::string(loc.str() + ": " + msg);
    }

    void Lexer::advance(int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            current_char = text[++loc.idx];

            if (current_char == '\n')
            {
                loc.line++;
            }

            loc.col++;
        }
    }

    Token Lexer::next()
    {
        Location orig_loc = loc;

        if (loc.idx >= text.length())
        {
            return Token(orig_loc, TokenType::EOF_, "");
        }

        for (const auto &pair : regexes)
        {
            // Extract the regex for this token type and test it on the source code

            std::string substr = text.substr(loc.idx);
            std::regex regex(pair.first);
            TokenType type = pair.second;

            std::smatch sm;
            std::regex_search(substr, sm, regex);

            if (sm.empty())
            {
                continue;
            }

            advance(sm.str().length());

            return Token(orig_loc, type, sm.str());
        }

        raise_error("illegal character: " + std::string(1, current_char));
        return Token();
    }

} // namespace pluto