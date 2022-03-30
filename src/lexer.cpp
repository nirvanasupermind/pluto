#include <string>
#include <vector>
#include <map>
#include <cstdint>

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
            else if (current_char() == '\'')
            {
                tokens.push_back(generate_char());
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
                int orig_line = line;

                advance();

                if (current_char() == '|')
                {
                    tokens.push_back(Token(orig_line, OR));
                    advance();
                }
                else
                {
                    tokens.push_back(Token(orig_line, BOR));
                }
            }
            else if (current_char() == '&')
            {
                int orig_line = line;

                advance();

                if (current_char() == '&')
                {
                    tokens.push_back(Token(orig_line, AND));
                    advance();
                }
                else
                {
                    tokens.push_back(Token(orig_line, BAND));
                }
            }
            else if (current_char() == '^')
            {
                int orig_line = line;

                advance();

                if (current_char() == '^')
                {
                    tokens.push_back(Token(orig_line, XOR));
                    advance();
                }
                else
                {
                    tokens.push_back(Token(orig_line, BXOR));
                }
            }
            else if (current_char() == '!')
            {
                int orig_line = line;

                advance();

                if (current_char() == '=')
                {
                    tokens.push_back(Token(orig_line, NE));
                    advance();
                }
                else
                {
                    tokens.push_back(Token(orig_line, NOT));
                }
            }
            else if (current_char() == '~')
            {
                tokens.push_back(Token(line, BNOT));
                advance();
            }
            else if (current_char() == '<')
            {
                int orig_line = line;

                advance();

                if (current_char() == '<')
                {
                    tokens.push_back(Token(orig_line, LSHIFT));
                    advance();
                }
                else if (current_char() == '=')
                {
                    tokens.push_back(Token(orig_line, LTE));
                    advance();
                }
                else
                {
                    tokens.push_back(Token(orig_line, LT));
                }
            }
            else if (current_char() == '>')
            {
                int orig_line = line;

                advance();

                if (current_char() == '>')
                {
                    tokens.push_back(Token(orig_line, RSHIFT));
                    advance();
                }
                else if (current_char() == '=')
                {
                    tokens.push_back(Token(orig_line, GTE));
                    advance();
                }
                else
                {
                    tokens.push_back(Token(orig_line, GT));
                }
            }
            else if (current_char() == '=')
            {
                int orig_line = line;

                advance();

                if (current_char() == '=')
                {
                    tokens.push_back(Token(orig_line, EE));
                    advance();
                }
                else
                {
                    tokens.push_back(Token(orig_line, EQ));
                }
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
            else if (current_char() == '{')
            {
                tokens.push_back(Token(line, LCURLY));
                advance();
            }
            else if (current_char() == '}')
            {
                tokens.push_back(Token(line, RCURLY));
                advance();
            }
            else if (current_char() == '[')
            {
                tokens.push_back(Token(line, LBRACKET));
                advance();
            }
            else if (current_char() == ']')
            {
                tokens.push_back(Token(line, RBRACKET));
                advance();
            }
            else if (current_char() == ',')
            {
                tokens.push_back(Token(line, COMMA));
                advance();
            }
            else if (current_char() == ';')
            {
                tokens.push_back(Token(line, SEMICOLON));
                advance();
            }
            else if (current_char() == '#')
            {
                while (current_char() != '\n')
                {
                    advance();
                }
            }
            else
            {
                std::string s(1, current_char());
                raise_error("invalid character '" + s + "'");
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

            // if (current_char() == 'y' || current_char() == 'Y')
            // {
            //     if (++y_count >= 2 || dot_count >= 1)
            //     {
            //         break;
            //     }
            // }

            val = val + current_char();
            advance();
        }

        if (val == ".")
        {
            return Token(line, DOT);
        }
        else if (dot_count == 1)
        {
            return Token(line, DOUBLE, std::stod(val));
        }
        else
        {
            return Token(line, INT, (std::int32_t)std::stol(val));
        }
    }

    Token Lexer::generate_char()
    {
        int orig_line = line; // Important because strings may be multiline

        unsigned char val;

        advance();

        if (current_char() == '\'')
        {
            raise_error("empty character literal");
        }

        if (current_char() == '\\')
        {
            advance();
            if (escape.count(current_char()) == 0)
            {
                val = current_char();
            }
            else
            {
                val = escape[current_char()];
            }
            advance();
        }
        else
        {
            val = current_char();
            advance();
        }

        if (pos >= text.length())
        {
            raise_error("unfinished character literal");
        }

        if(current_char() != '\'') {
            raise_error("multi-character literal");
        }
        
        advance();

        return Token(orig_line, CHAR, val);
    }

    Token Lexer::generate_string()
    {
        int orig_line = line; // Important because strings may be multiline

        std::string val;

        advance();

        while (current_char() != '"')
        {
            if (current_char() == '\\')
            {
                advance();
                if (escape.count(current_char()) == 0)
                {
                    val = val + current_char();
                }
                else
                {
                    val = val + escape[current_char()];
                }
                advance();
                continue;
            }

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

        if (name == "true")
        {
            return Token(line, TRUE);
        }
        else if (name == "false")
        {
            return Token(line, FALSE);
        }
        else if (name == "nil")
        {
            return Token(line, NIL);
        }
        else if (name == "var")
        {
            return Token(line, VAR);
        }
        else if (name == "const")
        {
            return Token(line, CONST);
        }
        else if (name == "if")
        {
            return Token(line, IF);
        }
        else if (name == "else")
        {
            return Token(line, ELSE);
        }
        else if (name == "for")
        {
            return Token(line, FOR);
        }
        else if (name == "while")
        {
            return Token(line, WHILE);
        }
        else if (name == "def")
        {
            return Token(line, DEF);
        }
        else if (name == "return")
        {
            return Token(line, RETURN);
        }
        else if (name == "lambda")
        {
            return Token(line, LAMBDA);
        }
        else if (name == "class")
        {
            return Token(line, CLASS);
        }
        else if (name == "module")
        {
            return Token(line, MODULE);
        }
        else if (name == "include")
        {
            return Token(line, INCLUDE);
        }
        else
        {
            return Token(line, NAME, name, true);
        }
    }
}