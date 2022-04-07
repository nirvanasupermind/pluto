#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>

#include "tokens.h"
#include "nodes.h"

namespace pluto {

class Parser {
private:
    std::vector<Token> tokens;
    std::size_t pos;
    Token current;

    void raise_error() const;
    void advance();

    std::shared_ptr<Node> expr();
    std::shared_ptr<Node> term();
    std::shared_ptr<Node> factor();
public:
    Parser(const std::vector<Token>& tokens);

    std::shared_ptr<Node> parse();
};

} // namespace pluto


#endif // PARSER_H