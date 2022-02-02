#include <string>
#include <vector>
#include <iostream>

#include "parser.h"
#include "tokens.h"
#include "nodes.h"

namespace Parser {
    Parser::Parser(std::string filename, std::vector<Tokens::Token> tokens) {
        this->filename = filename;
        this->tokens = tokens;
        index = 0;
    }

    Parser::~Parser() {
        Nodes::free_node(node);
    }

    void Parser::error() {
        PARSER_EMPTY_NODE;
        throw std::string(filename + ":" + std::to_string(current().line) + ": syntax error");
    }

    void Parser::advance() {
        index++;
    }

    Tokens::Token Parser::current() {
        return tokens[index];
    }

    Nodes::Node *Parser::parse() {
        node = file(Tokens::EOF_);
        return node;
    }

    Nodes::Node *Parser::file(Tokens::TokenType end) {
        int line = current().line;

        if (current().type == end) {
            advance();
            PARSER_EMPTY_NODE;
            return node;
        }

        std::vector<Nodes::Node *> stmts;


        while (current().type != end) {
            stmts.push_back(stmt());
        }

        if (current().type != end)
            error();

        advance();

        Nodes::Node *result = new Nodes::Node(line, Nodes::FileNode, stmts);
        
        return result;
    }

    Nodes::Node *Parser::stmt() {
        if (current().type == Tokens::VAR)
            return var();

        if (current().type == Tokens::LCURLY)
            return block();

        if (current().type == Tokens::IF)
            return if_();

        if (current().type == Tokens::FOR)
            return for_();

        if (current().type == Tokens::WHILE)
            return while_();

        Nodes::Node *result = expr();

        if (current().type != Tokens::SEMICOLON)
            error();

        advance();

        return result;
    }

    Nodes::Node *Parser::while_() {
        int line = current().line;

        if (current().type != Tokens::WHILE)
            error();

        advance();

        if (current().type != Tokens::LPAREN) 
            error();

        advance();

        Nodes::Node *cond = expr();

        if (current().type != Tokens::RPAREN) 
            error();

        advance();
        
        Nodes::Node *body = block();
        
        return new Nodes::Node(line, Nodes::WhileNode, cond, body);
    }

    Nodes::Node *Parser::for_() {
        if (current().type != Tokens::FOR)
            error();

        int line = current().line;

        advance();

        if (current().type != Tokens::LPAREN) 
            error();

        advance();

        Nodes::Node *node_a = stmt();
        Nodes::Node *node_b = stmt();
        Nodes::Node *node_c = stmt();

        if (current().type != Tokens::RPAREN) 
            error();

        advance();
        
        Nodes::Node *body = block();
        
        return new Nodes::Node(line, Nodes::ForNode, node_a, node_b, node_c, body);
    }


    Nodes::Node *Parser::if_() {

        int line = current().line;

        if (current().type != Tokens::IF)
            error();

        advance();

        if (current().type != Tokens::LPAREN) 
            error();

        advance();

        Nodes::Node *cond = expr();

        if (current().type != Tokens::RPAREN) 
            error();

        advance();
        
        Nodes::Node *body = block();

        advance();
        
        if (current().type == Tokens::ELSE) {
            advance();

            Nodes::Node *else_body = block();


            return new Nodes::Node(line, Nodes::IfElseNode, cond, body, else_body);
        }
            
        return new Nodes::Node(line, Nodes::IfNode, cond, body);
    }

    Nodes::Node *Parser::block() {
        if (current().type != Tokens::LCURLY)
            error();

        int line = current().line;

        advance();

        std::vector<Nodes::Node *> stmts = file(Tokens::RCURLY)->stmts;

        return new Nodes::Node(line, Nodes::BlockNode, stmts);
    }

    Nodes::Node *Parser::var() {  
        if (current().type != Tokens::VAR)
            error();

        int line = current().line;

        advance();
        
        if (current().type != Tokens::SYMBOL)
            error();

        std::string name = current().symbol;

        advance();

        if (current().type != Tokens::EQ)
            error();
        
        advance();

        Nodes::Node *val = expr();

        if (current().type != Tokens::SEMICOLON)
            error();
        
        advance();

        return new Nodes::Node(line, Nodes::VarNode, name, val);
    }

    Nodes::Node *Parser::expr() {
        return eq();
    }

    // Nodes::Node *Parser::ret() {
    //     int line = current().line;

    //     advance();

    //     Nodes::Node *result = expr();

    //     return new Nodes::Node(line, Nodes::ReturnNode, result);
    // }


    Nodes::Node *Parser::eq() {
        Nodes::Node *result = xor_();

        if (current().type == Tokens::EQ) {
            advance();
            return new Nodes::Node(result->line, Nodes::EQNode, result, expr());
        }

        return result;
    }

    Nodes::Node *Parser::xor_() {
        Nodes::Node *result = and_();

        while(current().type != Tokens::EOF_ && current().type == Tokens::XOR) {
            if (current().type == Tokens::XOR) {
                advance();
                result = new Nodes::Node(result->line, Nodes::XorNode, result, and_());
            }
        }

        return result;
    }

    Nodes::Node *Parser::and_() {
        Nodes::Node *result = or_();

        while(current().type != Tokens::EOF_ && current().type == Tokens::AND) {
            if (current().type == Tokens::AND) {
                advance();
                result = new Nodes::Node(result->line, Nodes::AndNode, result, or_());
            }
        }

        return result;
    }

    Nodes::Node *Parser::or_() {
        Nodes::Node *result = bitxor_();

        while(current().type != Tokens::EOF_ && current().type == Tokens::OR) {
            if (current().type == Tokens::OR) {
                advance();
                result = new Nodes::Node(result->line, Nodes::OrNode, result, bitxor_());
            }
        }

        return result;
    }

    Nodes::Node *Parser::bitxor_() {
        Nodes::Node *result = bitand_();

        while(current().type != Tokens::EOF_ && current().type == Tokens::BITXOR) {
            if (current().type == Tokens::BITXOR) {
                advance();
                result = new Nodes::Node(result->line, Nodes::BitXorNode, result, bitand_());
            }
        }

        return result;
    }

    Nodes::Node *Parser::bitand_() {
        Nodes::Node *result = bitor_();

        while(current().type != Tokens::EOF_ && current().type == Tokens::BITAND) {
            if (current().type == Tokens::BITAND) {
                advance();
                result = new Nodes::Node(result->line, Nodes::BitAndNode, result, bitor_());
            }
        }

        return result;
    }

    Nodes::Node *Parser::bitor_() {
        Nodes::Node *result = ee();

        while(current().type != Tokens::EOF_ && current().type == Tokens::BITOR) {
            if (current().type == Tokens::BITOR) {
                advance();
                result = new Nodes::Node(result->line, Nodes::BitOrNode, result, ee());
            }
        }

        return result;
    }

    Nodes::Node *Parser::ee() {
        Nodes::Node *result = comp();

        while(current().type != Tokens::EOF_ && (current().type == Tokens::EE || current().type == Tokens::NE)) {
            if (current().type == Tokens::EE) {
                advance();
                result = new Nodes::Node(result->line, Nodes::EENode, result, comp());
            } else if (current().type == Tokens::NE) {
                advance();
                result = new Nodes::Node(result->line, Nodes::NENode, result, comp());
            }
        }

        return result;
    }

    Nodes::Node *Parser::comp() {
        Nodes::Node *result = shift();

        while (current().type != Tokens::EOF_ && (current().type == Tokens::LT || current().type == Tokens::GT || current().type == Tokens::LE || current().type == Tokens::GE)) {
            if (current().type == Tokens::LT) {
                advance();
                result = new Nodes::Node(result->line, Nodes::LTNode, result, shift());
            } else if (current().type == Tokens::GT) {
                advance();
                result = new Nodes::Node(result->line, Nodes::GTNode, result, shift());
            } else if (current().type == Tokens::LE) {
                advance();
                result = new Nodes::Node(result->line, Nodes::LENode, result, shift());
            } else if (current().type == Tokens::GE) {
                advance();
                result = new Nodes::Node(result->line, Nodes::GENode, result, shift());
            }
        }

        return result;
    }


    Nodes::Node *Parser::shift() {
        Nodes::Node *result = add();

        while (current().type != Tokens::EOF_ && (current().type == Tokens::LSHIFT || current().type == Tokens::RSHIFT)) {
            if (current().type == Tokens::LSHIFT) {
                advance();
                result = new Nodes::Node(result->line, Nodes::LshiftNode, result, add());
            } else if (current().type == Tokens::RSHIFT) {
                advance();
                result = new Nodes::Node(result->line, Nodes::RshiftNode, result, add());
            }
        }

        return result;
    }

    Nodes::Node *Parser::add() {
        Nodes::Node *result = term();

        while (current().type != Tokens::EOF_ && (current().type == Tokens::PLUS || current().type == Tokens::MINUS)) {
            if (current().type == Tokens::PLUS) {
                advance();
                result = new Nodes::Node(result->line, Nodes::AddNode, result, term());
            } else if (current().type == Tokens::MINUS) {
                advance();
                result = new Nodes::Node(result->line, Nodes::SubtractNode, result, term());
            }
        }

        return result;
    }

    Nodes::Node *Parser::term() {
        Nodes::Node *result = exponent();

        while (current().type != Tokens::EOF_ && (current().type == Tokens::MULTIPLY || current().type == Tokens::DIVIDE)) {
            if (current().type == Tokens::MULTIPLY) {
                advance();
                result = new Nodes::Node(result->line, Nodes::MultiplyNode, result, exponent());
            } else if (current().type == Tokens::DIVIDE) {
                advance();
                result = new Nodes::Node(result->line, Nodes::DivideNode, result, exponent());
            }
        }

        return result;
    }

    Nodes::Node *Parser::exponent() {
        Nodes::Node *result = factor();

        while (current().type != Tokens::EOF_ && current().type == Tokens::POWER) {
            if (current().type == Tokens::POWER) {
                advance();
                result = new Nodes::Node(result->line, Nodes::PowerNode, result, factor());
            }
        }

        return result;
    }

    Nodes::Node *Parser::factor() {
        Tokens::Token current_token = current();


        if (current_token.type == Tokens::LPAREN) {
            advance();
            Nodes::Node *result = expr();

            if (current().type != Tokens::RPAREN) 
                error();

            advance();
            return result;
        } else if (current_token.type == Tokens::BYTE) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::ByteNode, current_token.byte);
        } else if (current_token.type == Tokens::NUMBER) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::NumberNode, current_token.value);
        } else if (current_token.type == Tokens::TRUE) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::TrueNode);
        } else if (current_token.type == Tokens::FALSE) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::FalseNode);
        } else if (current_token.type == Tokens::NIL) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::NilNode);
        } else if (current_token.type == Tokens::SYMBOL) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::SymbolNode, current_token.symbol);
        } else if (current_token.type == Tokens::PLUS) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::PlusNode, factor());
        } else if (current_token.type == Tokens::MINUS) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::MinusNode, factor());
        } else if (current_token.type == Tokens::NOT) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::NotNode, factor());
        } else if (current_token.type == Tokens::BITNOT) {
            advance();
            return new Nodes::Node(current_token.line, Nodes::BitNotNode, factor());
        }

        error();
    }
}