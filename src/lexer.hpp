#include "./tokens.hpp"
#include <vector>
#include <iostream>

namespace pluto {
    const std::string WHITESPACE = " \n\t";
    const std::string DIGITS = "0123456789";

    class Lexer {
        public:
            std::string path;
            std::string text;
            int index;

            Lexer(std::string path, std::string text) {
                this->path = path;
                this->text = text + '\0';
                index = 0;

                std::cout << "char: ";
                std::cout << current_char();
            }

            void advance() {
                index++;
            }

            char current_char() {
                return text[index];
            }    

            std::vector<Token> get_tokens() {
                std::vector<Token> tokens;
                
                // while(current_char() != '\0') {
                //     if(WHITESPACE.find(current_char())) {
                //         advance();
                //     } else if(current_char() == '+') {
                //         advance();
                //         tokens.push_back(Token("PLUS"));
                //     } else if(current_char() == '-') {
                //         advance();
                //         tokens.push_back(Token("MINUS"));
                //     } else if(current_char() == '*') {
                //         advance();
                //         tokens.push_back(Token("MULTIPLY"));
                //     } else if(current_char() == '/') {
                //         advance();
                //         tokens.push_back(Token("DIVIDE"));
                //     } else if(current_char() == '(') {
                //         advance();
                //         tokens.push_back(Token("LPAREN"));
                //     } else if(current_char() == ')') {
                //         advance();
                //         tokens.push_back(Token("RPAREN"));
                //     } 
                // }

                // tokens.push_back(Token("EOF_"));
                
                // return tokens;
            }
    };
}