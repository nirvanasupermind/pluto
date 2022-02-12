#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>

#include "token.h"
#include "node.h"

namespace pluto
{
    class Parser
    {
    private:
        std::vector<Token> tokens;
        std::size_t pos;
        Token current;

        void raise_error() const;
        void advance();

        std::unique_ptr<Node> additive_expr();
        std::unique_ptr<Node> multiplicative_expr();
        std::unique_ptr<Node> basic_expr();

    public:
        Parser(const std::vector<Token> &tokens);

        std::unique_ptr<Node> parse();
    };

}

#endif