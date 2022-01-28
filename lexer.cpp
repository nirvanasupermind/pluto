#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

#include "tokens.h"
#include "lexer.h"

namespace Lexer {
    Lexer::Lexer(std::string filename, std::string text) {
        this->filename = filename;
        this->text = text;
        index = 0;
        advance();
    }

    void Lexer::advance() {
        current_char = text[index++];
        if(current_char == "\n")
            line++;
    }

    std::vector<Tokens::Token> Lexer::get_tokens() {
        std::vector<Tokens::Token> tokens;

        while (index <= text.length()) {
            if (current_char.find_first_of(WHITESPACE) != std::string::npos) {
                advance();
            } else if (current_char == "." || current_char.find_first_of(DIGITS) != std::string::npos) {
                tokens.push_back(get_number());
            } else if (current_char.find_first_of(NONDIGITS) != std::string::npos) {
                tokens.push_back(get_symbol());
            } else if (current_char == "+") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::PLUS));
            } else if (current_char == "-") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::MINUS));
            } else if (current_char == "*") {
                advance();
                if (current_char == "*") {
                    advance();
                    tokens.push_back(Tokens::Token(line, Tokens::POWER));
                } else
                    tokens.push_back(Tokens::Token(line, Tokens::MULTIPLY));
            } else if (current_char == "/") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::DIVIDE));
            } else if (current_char == "(") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::LPAREN));
            } else if (current_char == ")") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::RPAREN));
            } else if (current_char == "{") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::LCURLY));
            } else if (current_char == "}") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::RCURLY));
            } else if (current_char == "=") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::EQ));
            } else if (current_char == ";") {
                advance();
                tokens.push_back(Tokens::Token(line, Tokens::SEMICOLON));
            } else {
                throw filename + ":" + std::to_string(line) + ": illegal character '" + current_char + "'";
            }
        }

        tokens.push_back(Tokens::Token(line, Tokens::EOF_));

        return tokens;
    }

    Tokens::Token Lexer::get_number() {
        int decimal_point_count = 0;
        std::string number_str = current_char;

        advance();

        while (index <= text.length() && (current_char == "." || current_char.find_first_of(DIGITS) != std::string::npos)) {
            if (current_char == ".")
                if (++decimal_point_count > 1)
                    break;
            
            number_str += current_char;
            advance();
        }

        if (number_str[0] == '.')
            number_str = "0" + number_str;

        if (number_str[number_str.length() - 1] == '.')
            number_str += "0";

        if(decimal_point_count <= 1 && (current_char == "y" || current_char == "Y")) {
            advance();
            return Tokens::Token(line, Tokens::BYTE, (std::int8_t)std::stoi(number_str));
        }

        return Tokens::Token(line, Tokens::NUMBER, std::stod(number_str));
    }

    Tokens::Token Lexer::get_symbol() {
        std::string symbol_str = current_char;

        advance();

        while (index <= text.length() && current_char.find_first_of(DIGITS + NONDIGITS) != std::string::npos) {
            symbol_str += current_char;
            advance();
        }
        
        if(symbol_str == "true") {
            return Tokens::Token(line, Tokens::TRUE);
        } else if(symbol_str == "false") {
            return Tokens::Token(line, Tokens::FALSE);
        } else if(symbol_str == "nil") {
            return Tokens::Token(line, Tokens::NIL);
        } else if(symbol_str == "var") {
            return Tokens::Token(line, Tokens::VAR);
        } else {
            return Tokens::Token(line, Tokens::SYMBOL, symbol_str);
        }
    }

    void print_tokens(std::vector<Tokens::Token>& tokens) {
        for (auto& token : tokens)
            std::cout << token.to_string() << '\n';
    }
}