#include "location.h"
#include "token.h"
#include "lexer.h"

namespace pluto
{

    Lexer::Lexer(const std::string &text)
        : text(text), loc(Location(0, 1, 0)), current(0)
    {
        advance();
    }

    void Lexer::advance()
    {
        if (loc.idx < text.length())
        {
            current = text.at(loc.idx++);
        }
        else
        {
            current = EOF; 
        }
    }

    Token Lexer::gettok()
    {
        if (current == EOF)
        {
            // EOF.
            return Token(loc, TokenType::EOF_, "EOF");
        }
        
        if (WHITESPACE.find(current) != std::string::npos || NEWLINE.find(current) != std::string::npos)
        {
            // Whitespace or newline.

            advance();
            return gettok();
        }

        if (current == '#')
        {
            // Comment until end of line.
            
            do
                advance();
            while (current != EOF && NEWLINE.find(current) == std::string::npos);

            if (current != EOF)
                return gettok();
        }

        if (isdigit(current) || current == '.')
        {
            int dot_count = 0;
            Location original_loc = loc.clone();

            // Number: [0-9.]+
            std::string result;
            do
            {
                if(current == '.') 
                    if(++dot_count >= 2)
                        break;

                result += current;
                advance();
            } while (isdigit(current) || current == '.');

            if (dot_count == 0)
                return Token(original_loc, TokenType::INT, result);     
                      
            return Token(original_loc, TokenType::DOUBLE, result);
        }

        // Anything else is just a symbol.

        Token result = Token(loc, TokenType::SYMBOL, std::string(1, current));

        advance();

        return result;
    }

} // namespace pluto