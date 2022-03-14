#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <string>
#include <memory>
#include <vector>

#include "src/token.cpp"
#include "src/lexer.cpp"
#include "src/node.cpp"
#include "src/parser.cpp"
#include "src/concept.cpp"
#include "src/env.cpp"
#include "src/entity.cpp"
#include "src/builtins.cpp"
#include "src/arguments.cpp"
#include "src/interpreter.cpp"

void run(std::string filename, std::string text)
{
    pluto::Lexer lexer(filename, text);
    std::vector<pluto::Token> tokens = lexer.generate_tokens();
    
    pluto::Parser parser(filename, tokens);
    std::shared_ptr<pluto::Node> tree = parser.parse();

    std::shared_ptr<pluto::Env> global_env(new pluto::Env());
    // global_env->set("Object", std::move(pluto::Builtins::class_object));
    // global_env->set("String", std::move(pluto::Builtins::class_string));
    // global_env->set("Func", std::move(pluto::Builtins::class_func));

    pluto::Interpreter interpreter(filename);
    // final result is stored in entity
    std::shared_ptr<pluto::Entity> entity = interpreter.visit(std::move(tree), std::move(global_env));
    
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