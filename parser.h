#ifndef PARSER_H
#define PARSER_H


#include <iostream>
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
            Nodes::Node *function();
            Nodes::Node *while_();
            Nodes::Node *for_();
            Nodes::Node *if_();
            Nodes::Node *block();
            Nodes::Node *var();
            Nodes::Node *expr();
            Nodes::Node *eq();
            Nodes::Node *ee();
            Nodes::Node *or_();
            Nodes::Node *and_();
            Nodes::Node *xor_();
            Nodes::Node *bitor_();
            Nodes::Node *bitand_();
            Nodes::Node *bitxor_();
            Nodes::Node *comp();
            Nodes::Node *shift();
            Nodes::Node *add();
            Nodes::Node *term();
            Nodes::Node *exponent();
            Nodes::Node *factor();

            std::vector<std::string> arg_list(Tokens::TokenType start, Tokens::TokenType end);
    };
}

#endif // PARSER_H