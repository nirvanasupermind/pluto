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

    void Lexer::raise_error(std::string msg)
    {
        throw std::string(filename + ":" + std::to_string(line) + ": " + msg);
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
            else if (std::isalpha(current_char()) || current_char() == '_')
            {
                tokens.push_back(generate_name());
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
            else if (current_char() == '%')
            {
                tokens.push_back(Token(line, MOD));
                advance();
            }
            else if (current_char() == '|')
            {
                advance();
                if (current_char() == '|')
                {
                    tokens.push_back(Token(line, OR));
                }
            }
            else if (current_char() == '&')
            {
                advance();
                if (current_char() == '&')
                {
                    tokens.push_back(Token(line, AND));
                }
            }
            else if (current_char() == '^')
            {
                advance();
                if (current_char() == '&')
                {
                    tokens.push_back(Token(line, XOR));
                }
            }
            else if (current_char() == '!')
            {
                tokens.push_back(Token(line, NOT));
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
                std::string s(1, current_char());
                raise_error("illegal character '" + s + "'");
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
        int orig_line = line; // Important because strings may be multiline

        std::string val;

        advance();

        while (current_char() != '"')
        {
            if (pos >= text.length())
            {
                raise_error("unfinished string literal");
            }

            val = val + current_char();
            advance();
        }

        advance();

        return Token(orig_line, STRING, val);
    }

    Token Lexer::generate_name()
    {
        std::string name;

        while (pos < text.length() && (isalnum(current_char()) || current_char() == '_'))
        {
            name = name + current_char();
            advance();
        }

        advance();

        if (name == "true")
        {
            return Token(line, TRUE);
        }
        else if (name == "false")
        {
            return Token(line, FALSE);
        }
        else
        {
            return Token(line, NAME, name);
        }
    }
}