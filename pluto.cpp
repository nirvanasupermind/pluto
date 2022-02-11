#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <vector>
#include <string>

#include "src/token.cpp"
#include "src/lexer.cpp"

void run(std::string filename, std::string text)
{
    pluto::Lexer lexer(filename, text);
    std::vector<pluto::Token> tokens = lexer.generate_tokens();

    for(int i = 0; i < tokens.size(); i++) {
        std::cout << tokens.at(i).to_string() << '\n';
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: pluto [script]" << '\n';
    }
    else
    {
        std::string filename(argv[1]);
        std::ifstream inFile;

        inFile.open(filename);

        std::stringstream strStream;
        strStream << inFile.rdbuf();

        std::string text = strStream.str();
        
        try
        {
            run(filename, text);
        }
        catch (std::string e)
        {   
            std::cerr << e << '\n';
        }
    }
}