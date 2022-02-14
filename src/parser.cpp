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
        throw std::string(filename + ":" + std::to_string(current().line) + ": syntax error");
    }

    void Parser::advance()
    {
        pos++;
    }

    Token Parser::current()
    {
        return tokens[pos];
    }

    std::unique_ptr<Node> Parser::parse()
    {
        std::unique_ptr<Node> result = expr();

        if (current().type != EOF_)
        {
            raise_error();
        }

        return result;
    }

    std::unique_ptr<Node> Parser::expr()
    {
        return additive_expr();
    }

    std::unique_ptr<Node> Parser::additive_expr()
    {
        std::unique_ptr<Node> result = multiplicative_expr();

        while (pos < tokens.size() && (current().type == PLUS || current().type == MINUS))
        {
            if (current().type == PLUS)
            {
                // std::cout << result.get()->to_string() << '\n';
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

        while (pos < tokens.size() && (current().type == MULTIPLY || current().type == DIVIDE))
        {
            if (current().type == MULTIPLY)
            {
                advance();
                result = std::unique_ptr<Node>(new MultiplyNode(result.get()->line, std::move(result), prefix_expr()));
            }
            else if (current().type == DIVIDE)
            {
                advance();
                result = std::unique_ptr<Node>(new MultiplyNode(result.get()->line, std::move(result), prefix_expr()));
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

            if(current().type != RPAREN) {
                raise_error();
            }

            advance();

            return result;
        } else if (current_token.type == INT)
        {
            advance();
            return std::unique_ptr<Node>(new IntNode(current_token.line, current_token.int_val));
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

        raise_error();
    }
}
