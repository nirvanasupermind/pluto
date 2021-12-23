#include <iostream>
#include <fstream>
#include "src/lexer.hpp"


int main(int argc, char *argv[]) {
    if(argc >= 1) {
        std::string path = argv[1];
    
        std::ifstream file(path);

        std::string text;
        std::string line;

        // Use a while loop together with the getline() function to read the file line by line
        while (std::getline(file, line)) {
            if(text.length() == 0)
                text = line;
            else
                text = text + "\n" + line;
        }

        // Close the file
        file.close();

        pluto::Lexer lexer(text);

        std::vector<pluto::Token> tokens = lexer.get_tokens();

        for(int i = 0; i < tokens.size(); i++) {
            std::cout << static_cast<std::string>(tokens.at(i)) + "\n";
        }
    }
}