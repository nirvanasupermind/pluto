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
        pos = 0;
        line = 1;
    }

    void Lexer::raise_error()
    {
        throw std::string(filename + ":" + std::to_string(line) + ": lexical error");
    }

    void Lexer::advance()
    {
        pos++;

        if (current_char() == '\n')
        {
            line++;
        }
    }

    char Lexer::current_char()
    {
        return text[pos];
    }

    std::vector<Token> Lexer::generate_tokens()
    {
        std::vector<Token> tokens;

        while (pos < text.length())
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
                raise_error();
            }
        }

        tokens.push_back(Token(line, EOF_));

        return tokens;
    }

    Token Lexer::generate_number()
    {
        std::string val;
        int dot_count = 0;

        while (pos < text.length() && (std::isdigit(current_char()) || current_char() == '.'))
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

        if (dot_count == 0)
        {
            return Token(line, INT, std::stoi(val));
        }
        else
        {
            return Token(line, DOUBLE, std::stod(val));
        }
    }

    Token Lexer::generate_string()
    {
        std::string val;
        int dot_count = 0;

        advance();

        while (current_char() != '"')
        {
            if (pos >= text.length())
            {
                raise_error();
            }

            val = val + current_char();
            advance();
        }

        advance();

        return Token(line, STRING, val);
    }
}