#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "tokens.h"
#include "nodes.h"

#define PARSER_EMPTY_NODE node = new Nodes::Node(current().line, Nodes::EmptyNode)

namespace Parser {
    class Parser {
        public:
            std::string filename;
            std::vector<Tokens::Token> tokens;
            std::size_t index;
            Nodes::Node *node;

            Parser(std::string, std::vector<Tokens::Token>);
            ~Parser();
            void error();
            void advance();
            Tokens::Token current();
            Nodes::Node *parse();
            Nodes::Node *file(Tokens::TokenType end);
            Nodes::Node *stmt();
            Nodes::Node *var();
            Nodes::Node *expr();
            Nodes::Node *eq();
            Nodes::Node *add();
            Nodes::Node *term();
            Nodes::Node *exponent();
            Nodes::Node *factor();
    };
}

#endif // PARSER_H