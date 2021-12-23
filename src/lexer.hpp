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
                if(current() == '\n')
                    ln++;
                index++;
            }

            char current() {
                return text[index];
            }

            std::vector<Token> get_tokens() {
                std::vector<Token> tokens;

                while(current() != '\0') {
                    if(WHITESPACE.find(current()) != std::string::npos) {
                        advance();
                    } else if(current() == '.' || DIGITS.find_first_of(current()) != std::string::npos) {
                        tokens.push_back(get_number());
                    } else {
                        tokens.push_back(Token(ln, (int)current()));
                        advance();
                    }
                }

                tokens.push_back(Token(ln, type_eof));

                return tokens;
            }

            Token get_number() {
                std::size_t decimal_point_count = 0;
                std::string number_str(1, current());
                advance();

                while (current() && (current() == '.' || DIGITS.find_first_of(current()) != std::string::npos)) {
                    if (current() == '.') {
                        if (++decimal_point_count > 1) {
                            break;
                        }
                    }

                    number_str += current();
                    advance();
                }

                if (number_str.at(0) == '.') {
                    number_str = '0' + number_str;
                }

                if (number_str.at(number_str.length() - 1) == '.') {
                    number_str += '0';
                }

                return Token(ln, type_number, std::stod(number_str));
            }
    };
}