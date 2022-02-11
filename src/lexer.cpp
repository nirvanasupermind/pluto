#include <string>
#include <vector>

#include "token.h"
#include "lexer.h"

namespace pluto
{
    Lexer::Lexer(std::string filename, std::string text)
    {
        this->filename = filename;
        this->text = text;
        position = 0;
        line = 1;
    }

    void Lexer::error()
    {
        throw filename + ":" + std::to_string(line) + ": lexical error";
    }

    void Lexer::advance()
    {
        position++;

        if (current_char() == '\n')
        {
            line++;
        }
    }

    char Lexer::current_char()
    {
        return text[position];
    }

    std::vector<Token> Lexer::generate_tokens()
    {
        std::vector<Token> tokens;

        while (position < text.length())
        {
            if (WHITESPACE.find(current_char()) != std::string::npos)
            {
                advance();
            }
            else if (current_char() == '"')
            {
                tokens.push_back(generate_string());
            }
            else if (std::isdigit(current_char()) || current_char() == '.')
            {
                tokens.push_back(generate_number());
            }
            else if (current_char() == '+')
            {
                tokens.push_back(Token(line, PLUS));
                advance();
            }
            else if (current_char() == '-')
            {
                tokens.push_back(Token(line, MINUS));
                advance();
            }
            else if (current_char() == '*')
            {
                tokens.push_back(Token(line, MULTIPLY));
                advance();
            }
            else if (current_char() == '/')
            {
                tokens.push_back(Token(line, DIVIDE));
                advance();
            }
            else if (current_char() == '(')
            {
                tokens.push_back(Token(line, LPAREN));
                advance();
            }
            else if (current_char() == ')')
            {
                tokens.push_back(Token(line, RPAREN));
                advance();
            }
            else
            {
                error();
            }
        }

        return tokens;
    }

    Token Lexer::generate_string()
    {
        std::string val;
        int dot_count = 0;

        advance();

        while (current_char() != '"')
        {
            if (position == text.length())
            {
                error();
            }

            val = val + current_char();
            advance();
        }

        advance();

        return Token(line, STRING, val);
    }

    Token Lexer::generate_number()
    {
        std::string val;
        int dot_count = 0;

        while (position < text.length() && (std::isdigit(current_char()) || current_char() == '.'))
        {
            if (current_char() == '.')
            {
                if (++dot_count >= 2)
                {
                    break;
                }
            }

            val = val + current_char();
            advance();
        }

        return Token(line, NUMBER, std::stod(val));
    }
}