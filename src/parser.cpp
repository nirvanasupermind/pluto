#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "token.h"
#include "node.h"
#include "parser.h"

namespace pluto
{
    Parser::Parser(std::string filename, std::vector<Token> tokens)
    {
        this->filename = filename;
        this->tokens = tokens;
        pos = 0;
    }

    void Parser::raise_error()
    {
        throw std::string(filename + ":" + std::to_string(current().line) + ": invalid syntax");
    }

    void Parser::advance()
    {
        pos++;
    }

    Token Parser::current()
    {
        return tokens.at(pos);
    }

    std::unique_ptr<Node> Parser::parse()
    {
        std::unique_ptr<Node> result = stmt();

        if (current().type != EOF_)
        {
            raise_error();
        }

        return result;
    }

    std::unique_ptr<Node> Parser::stmt()
    {
        std::unique_ptr<Node> result = expr();
        
        if (current().type != SEMICOLON)
        {
            raise_error();
        }

        advance();

        return result;
    }

    std::unique_ptr<Node> Parser::expr()
    {
        return band_expr();
    }

    std::unique_ptr<Node> Parser::band_expr()
    {
        std::unique_ptr<Node> result = bxor_expr();

        while (pos < tokens.size() && (current().type == BAND))
        {
            if (current().type == BAND)
            {
                advance();
                result = std::unique_ptr<Node>(new BAndNode(result.get()->line, std::move(result), band_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::bxor_expr()
    {
        std::unique_ptr<Node> result = and_expr();

        while (pos < tokens.size() && (current().type == BXOR))
        {
            if (current().type == BXOR)
            {
                advance();
                result = std::unique_ptr<Node>(new BXorNode(result.get()->line, std::move(result), bor_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::bor_expr()
    {
        std::unique_ptr<Node> result = and_expr();

        while (pos < tokens.size() && (current().type == BOR))
        {
            if (current().type == BOR)
            {
                advance();
                result = std::unique_ptr<Node>(new BOrNode(result.get()->line, std::move(result), and_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::and_expr()
    {
        std::unique_ptr<Node> result = xor_expr();

        while (pos < tokens.size() && (current().type == AND))
        {
            if (current().type == AND)
            {
                advance();
                result = std::unique_ptr<Node>(new AndNode(result.get()->line, std::move(result), xor_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::xor_expr()
    {
        std::unique_ptr<Node> result = or_expr();

        while (pos < tokens.size() && (current().type == XOR))
        {
            if (current().type == XOR)
            {
                advance();
                result = std::unique_ptr<Node>(new XorNode(result.get()->line, std::move(result), or_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::or_expr()
    {
        std::unique_ptr<Node> result = additive_expr();


        while (pos < tokens.size() && (current().type == OR))
        {
            if (current().type == OR)
            {
                advance();
                result = std::unique_ptr<Node>(new OrNode(result.get()->line, std::move(result), additive_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::additive_expr()
    {
        std::unique_ptr<Node> result = multiplicative_expr();

        while (pos < tokens.size() && (current().type == PLUS || current().type == MINUS))
        {
            if (current().type == PLUS)
            {
                advance();
                result = std::unique_ptr<Node>(new AddNode(result.get()->line, std::move(result), multiplicative_expr()));
            }
            else if (current().type == MINUS)
            {
                advance();
                result = std::unique_ptr<Node>(new SubtractNode(result.get()->line, std::move(result), multiplicative_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::multiplicative_expr()
    {
        std::unique_ptr<Node> result = prefix_expr();

        while (pos < tokens.size() && (current().type == MULTIPLY || current().type == DIVIDE || current().type == MOD))
        {
            if (current().type == MULTIPLY)
            {
                advance();
                result = std::unique_ptr<Node>(new MultiplyNode(result.get()->line, std::move(result), prefix_expr()));
            }
            else if (current().type == DIVIDE)
            {
                advance();
                result = std::unique_ptr<Node>(new DivideNode(result.get()->line, std::move(result), prefix_expr()));
            }
            else if (current().type == MOD)
            {
                advance();
                result = std::unique_ptr<Node>(new ModNode(result.get()->line, std::move(result), prefix_expr()));
            }
        }

        return result;
    }

    std::unique_ptr<Node> Parser::prefix_expr()
    {
        Token current_token = current();

        if (current_token.type == PLUS)
        {
            advance();
            return std::unique_ptr<Node>(new PlusNode(current_token.line, prefix_expr()));
        }
        else if (current_token.type == MINUS)
        {
            advance();
            return std::unique_ptr<Node>(new MinusNode(current_token.line, prefix_expr()));
        }
        else if (current_token.type == NOT)
        {
            advance();
            return std::unique_ptr<Node>(new NotNode(current_token.line, prefix_expr()));
        }
        else if (current_token.type == BNOT)
        {
            advance();
            return std::unique_ptr<Node>(new BNotNode(current_token.line, prefix_expr()));
        }

        return postfix_expr();
    }

    std::unique_ptr<Node> Parser::postfix_expr()
    {
        std::unique_ptr<Node> result = leaf_expr();

        return result;
    }

    std::unique_ptr<Node> Parser::leaf_expr()
    {

        Token current_token = current();
        
        if (current_token.type == LPAREN)
        {
            advance();

            std::unique_ptr<Node> result = expr();

            if (current().type != RPAREN)
            {
                raise_error();
            }

            advance();

            return result;
        }
        else if (current_token.type == INT)
        {
            advance();

            std::unique_ptr<Node> result = std::unique_ptr<Node>(new IntNode(current_token.line, current_token.int_val));

            return result;
        }
        else if (current_token.type == DOUBLE)
        {
            advance();
            return std::unique_ptr<Node>(new DoubleNode(current_token.line, current_token.double_val));
        }
        else if (current_token.type == STRING)
        {
            advance();
            return std::unique_ptr<Node>(new StringNode(current_token.line, current_token.string_val));
        }
        else if (current_token.type == TRUE)
        {
            advance();
            return std::unique_ptr<Node>(new TrueNode(current_token.line));
        }
        else if (current_token.type == FALSE)
        {
            advance();
            return std::unique_ptr<Node>(new FalseNode(current_token.line));
        }
        else if (current_token.type == NIL)
        {
            advance();
            return std::unique_ptr<Node>(new NilNode(current_token.line));
        }

        raise_error();
    }
}