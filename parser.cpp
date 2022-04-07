#include <string>
#include <memory>
#include <vector>

#include "parser.h"

namespace pluto {

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens),
    pos(0),
    current(Token(TokenType::EOF_))
{
    if (this->tokens.empty()) {
        this->tokens.push_back(TokenType::EOF_);
    } else if (this->tokens.back().type != TokenType::EOF_) {
        this->tokens.push_back(TokenType::EOF_);
    }
    advance();
}

void Parser::raise_error() const {
    throw std::string("Invalid syntax");
}

void Parser::advance() {
    current = tokens.at(pos++);
}

std::shared_ptr<Node> Parser::parse() {
    if (!current) {
        return std::shared_ptr<Node>();
    }

    std::shared_ptr<Node> result = expr();

    if (current) {
        raise_error();
    }

    return result;
}

std::shared_ptr<Node> Parser::expr() {
    std::shared_ptr<Node> result = term();

    while (current && (current.type == TokenType::PLUS || current.type == TokenType::MINUS)) {
        if (current.type == TokenType::PLUS) {
            advance();
            result = std::shared_ptr<AddNode>(new AddNode(std::move(result), term()));
        } else if (current.type == TokenType::MINUS) {
            advance();
            result = std::shared_ptr<SubtractNode>(new SubtractNode(std::move(result), term())); // Missin' std::make_shared :(
        }
    }

    return result;
}

std::shared_ptr<Node> Parser::term() {
    std::shared_ptr<Node> result = factor();

    while (current && (current.type == TokenType::MULTIPLY || current.type == TokenType::DIVIDE)) {
        if (current.type == TokenType::MULTIPLY) {
            advance();
            result = std::shared_ptr<MultiplyNode>(new MultiplyNode(std::move(result), factor()));
        } else if (current.type == TokenType::DIVIDE) {
            advance();
            result = std::shared_ptr<DivideNode>(new DivideNode(std::move(result), factor()));
        }
    }

    return result;
}

std::shared_ptr<Node> Parser::factor() {
    Token token = current;

    if (token.type == TokenType::LPAREN) {
        advance();
        std::shared_ptr<Node> result = expr();

        if (current.type != TokenType::RPAREN) {
            raise_error();
        }

        advance();
        return result;
    } else if (token.type == TokenType::NUMBER) {
        advance();
        return std::shared_ptr<NumberNode>(new NumberNode(token.value));
    } else if (token.type == TokenType::PLUS) {
        advance();
        return std::shared_ptr<PlusNode>(new PlusNode(factor()));
    } else if (token.type == TokenType::MINUS) {
        advance();
        return std::shared_ptr<MinusNode>(new MinusNode(factor()));
    }

    raise_error();
    return std::shared_ptr<Node>();
}

} // namespace pluto
