#include <vector> 
#include "./tokens.hpp"

namespace pluto {
    const std::string NUMERIC = ".0123456789";

    class Lexer {
        public:
            std::string input;
            std::vector<Token> tokens;

            int index;
            int line;

            Lexer(std::string input) {
                this->input = input + '\0';
                index = 0;
                line = 1;
            }

            void advance() {
                if(current_char() == '\n')
                    line++;

                index++;
            }

            char current_char() {
                return input[index];
            }

            void tokenizer() {
                while(current_char() != '\0') {
                    if(NUMERIC.find(current_char()) != std::string::npos) {
                        tokens.push_back(number());
                    } else if(current_char() == '+') {
                        advance();
                        tokens.push_back(Token(line, TokenType::PLUS));
                    } else {
                        throw "line " + std::to_string(line);
                    }
                }
            }

            Token number() {
                std::string val = "";
                int decimal_point_count = 0;

                while(current_char() != '\0' 
                      && NUMERIC.find(current_char()) != std::string::npos) {
                    if(current_char() == '.')
                        if(++decimal_point_count >= 2)
                            break;
                    
                    val += current_char();
            
                    advance();
                }

                if(val == ".")
                    return Token(line, TokenType::DOT);
                
                return Token(line, TokenType::NUMBER, std::stod(val));
            }
    };
};