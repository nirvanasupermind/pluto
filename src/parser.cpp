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
        return prefix_expr();
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

        if (current_token.type == INT)
        {
            advance();
            return std::unique_ptr<Node>(new IntNode(current_token.line, current_token.int_val));
        }
        else if (current_token.type == DOUBLE)
        {
            advance();
            return std::unique_ptr<Node>(new DoubleNode(current_token.line, current_token.double_val));
        }
        
        raise_error();
    }
}
