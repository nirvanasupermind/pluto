#include <vector>
#include "./tokens.hpp"

namespace pluto {
    const std::string WHITESPACE = " \n\t";
    const std::string DIGITS = "0123456789";

    class Lexer {
        public:
            std::string text;
            int ln;
            int index;

            Lexer(std::string text) {
                this->text = text + '\0';
                ln = 1;
                index = 0;
            }

            void advance() {
                if(current_char() == '\n')
                    ln++;
                index++;
            }

            char current_char() {
                return text[index];
            }

            std::vector<Token> get_tokens() {
                std::vector<Token> tokens;

                while(current_char() != '\0') {
                    if(WHITESPACE.find(current_char()) != std::string::npos) {
                        advance();
                    } else {
                        tokens.push_back(Token(ln, (int)current_char()));
                        advance();
                    }
                }

                return tokens;
            }
    };
}