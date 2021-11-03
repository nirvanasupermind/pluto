#include <iostream>
#include <fstream>
#include <streambuf>
#include "./lexer.hpp"

namespace pluto {
    void run(std::string path) {
        std::ifstream t(path);
        std::string text((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());

        Lexer lexer(path, text);
        std::vector<Token> tokens = lexer.get_tokens();

        for(int i = 0; i < tokens.size(); i++) {
            std::cout << static_cast<std::string>(tokens.at(i))+"\n";
        }
    }
};