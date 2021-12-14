#include <string> 
#include <iostream>

namespace pluto {
    enum TokenType {
        NUMBER,
        PLUS,
        DOT,
        EOF_
    };

    class Token {
        public:
            int line;
            TokenType type;
            double num_val;

            Token(int line, TokenType type) {
                this->line = line;
                this->type = type;
            }

            Token(int line, TokenType type, double num_val) {
                this->line = line;
                this->type = type;
                this->num_val = num_val;  
            }

            operator std::string() const {
                switch(type) {
                    case TokenType::NUMBER:
                        return "NUMBER:"+std::to_string(num_val);
                    case TokenType::PLUS:
                        return "PLUS";
                    case TokenType::DOT:
                        return "DOT";
                    default:
                        return "EOF";
                }
            }
    };
};