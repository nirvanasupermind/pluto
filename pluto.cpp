#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <vector>
#include <string>

#include "src/token.cpp"
#include "src/lexer.cpp"
#include "src/node.cpp"
#include "src/parser.cpp"
#include "src/env.cpp"
#include "src/entity.cpp"
#include "src/object.cpp"
#include "src/builtins.cpp"
#include "src/interpreter.cpp"

void run(std::string filename, std::string text)
{
    pluto::Lexer lexer(filename, text);
    std::vector<pluto::Token> tokens = lexer.generate_tokens();
    
    pluto::Parser parser(filename, tokens);
    std::unique_ptr<pluto::Node> tree = parser.parse();

    std::cout << tree->to_string() << '\n';
    
    pluto::Interpreter interpreter(filename);
    // final result is stored in entity
    std::unique_ptr<pluto::Entity> entity = interpreter.visit(std::move(tree));
    
    std::cout << entity->to_string() << '\n';
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