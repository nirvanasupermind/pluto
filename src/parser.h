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

        std::shared_ptr<Node> parse();
        std::shared_ptr<Node> program();
        std::shared_ptr<Node> stmt();
        std::shared_ptr<Node> var_assign_stmt();
        std::shared_ptr<Node> expr();
        std::shared_ptr<Node> band_expr();
        std::shared_ptr<Node> bxor_expr();
        std::shared_ptr<Node> bor_expr();
        std::shared_ptr<Node> and_expr();
        std::shared_ptr<Node> xor_expr();
        std::shared_ptr<Node> or_expr();
        std::shared_ptr<Node> shift_expr();
        std::shared_ptr<Node> equality_expr();
        std::shared_ptr<Node> comp_expr();
        std::shared_ptr<Node> additive_expr();
        std::shared_ptr<Node> multiplicative_expr();
        std::shared_ptr<Node> prefix_expr();
        std::shared_ptr<Node> postfix_expr();
        std::shared_ptr<Node> leaf_expr();
    };
}

#endif