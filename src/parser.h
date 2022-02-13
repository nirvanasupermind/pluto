#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "token.h"
#include "node.h"

namespace pluto
{
    class Parser
    {
    public:
        std::string filename;
        std::vector<Token> tokens;
        std::size_t pos;

        Parser(std::string filename, std::vector<Token> tokens);

        void raise_error();
        void advance();
        Token current();

        std::unique_ptr<Node> parse();
        std::unique_ptr<Node> expr();
        // std::unique_ptr<Node> additive_expr();
        // std::unique_ptr<Node> multiplicative_expr();
        std::unique_ptr<Node> prefix_expr();
        std::unique_ptr<Node> postfix_expr();
        std::unique_ptr<Node> leaf_expr();
    };

}

#endif