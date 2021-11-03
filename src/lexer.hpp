#include <string>
#include <vector>
#include <iostream>
#include "./tokens.hpp"

const std::string DIGITS = "0123456789";
const std::string WHITESPACE = " \n\t";

namespace pluto {
    class Lexer {
        public:
            std::string path;
            std::string text;
            std::size_t index;
            int line;

            Lexer(std::string path, std::string text) {
                this->path = path;
                this->text = text + '\0';
                index = 0;
                line = 1;
            }

            void error() {
                std::cout << "pluto: "+path+":"+std::to_string(line)+": lexical error\n";
                std::exit(1);
            }

            void advance() {
                index++;
            }

            char current_char() {
                return text[index];
            }

            std::vector<Token> get_tokens() {
                std::vector<Token> tokens;

                while(current_char() != '\0') {
                    if(WHITESPACE.find(current_char()) < WHITESPACE.length()) {
                        if(current_char() == '\n')
                            line++;
                        advance();
                    } else if(DIGITS.find(current_char()) < DIGITS.length()) {
                        tokens.push_back(get_number());
                    } else if(current_char() == '+') {
                        advance();
                        tokens.push_back(Token(line, "plus"));
                    } else if(current_char() == '-') {
                        advance();
                        tokens.push_back(Token(line, "minus"));
                    } else if(current_char() == '*') {
                        advance();
                        tokens.push_back(Token(line, "multiply"));
                    } else if(current_char() == '/') {
                        advance();
                        tokens.push_back(Token(line, "divide"));
                    } else if(current_char() == '(') {
                        advance();
                        tokens.push_back(Token(line, "lparen"));
                    } else if(current_char() == ')') {
                        advance();
                        tokens.push_back(Token(line, "rparen"));
                    } else {
                        error();
                    }
                }

                return tokens;
            }

            Token get_number() {
                std::string value = "";
                int decimal_point_count = 1;
                int ln = line;
                
                while(current_char() != '\0' && 
                     ((DIGITS + '.').find(current_char()) < (DIGITS + '.').length())) {
                    if(current_char() == '.')
                        if(++decimal_point_count > 1)
                            break;

                    value += current_char();
                    advance();
                }
                
                return Token(ln, "num", value);
            }
    };
};