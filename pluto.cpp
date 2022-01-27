#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <vector>
#include <string>

#include "tokens.cpp"
#include "lexer.cpp"
#include "nodes.cpp"
#include "parser.cpp"
#include "interpreter.cpp"
#include "values.cpp"
#include "scopes.cpp"

int main(int argc, char **argv) {
    if(argc <= 1) {
        // CODE FOR REPL/SHELL

        std::string filename("stdin");

        std::string text;
        std::vector<Tokens::Token> tokens;

        std::cout << "Welcome to Pluto 0.0"  << '\n';
        
        while (true) {
            try {
                std::cout << "> " << std::flush;
                std::getline(std::cin, text);
                if (std::cin.bad()) {
                    std::cerr << "IO error\n";
                    break;
                } else if (std::cin.eof()) {
                    std::cerr << "End of file\n";
                    break;
                }

                if(text == "exit") { return 0; }

                Lexer::Lexer lexer(filename, text);
                tokens = lexer.get_tokens();
                //Lexer::print_tokens(tokens);
                Parser::Parser parser(filename, tokens);
                Nodes::Node *tree = parser.parse();
                //Nodes::print_node(tree);

                Interpreter::Interpreter interpreter(filename);
                Scopes::Scope *global_scope = new Scopes::Scope();
                Values::Value *result = interpreter.visit(tree, global_scope);

                std::cout << result->to_string() << '\n';
            } catch (std::string e) {
                std::cerr << e << '\n';
            }
        }

        return 0;
    } else {
        // CODE FOR FILE

        std::string filename(argv[1]);
        std::ifstream inFile;
        inFile.open(filename); //open the input file

        std::stringstream strStream;
        strStream << inFile.rdbuf(); //read the file
        std::string text = strStream.str(); //text holds the content of the file
        std::vector<Tokens::Token> tokens;

        try {
            Lexer::Lexer lexer(filename, text);
            tokens = lexer.get_tokens();
            //Lexer::print_tokens(tokens);
            Parser::Parser parser(filename, tokens);
            Nodes::Node *tree = parser.parse();
            // Nodes::print_node(tree);

            Interpreter::Interpreter interpreter(filename);
             // std::cout << "hi" << '\n';
            Scopes::Scope *global_scope = new Scopes::Scope();
            Values::Value *result = interpreter.visit(tree, global_scope);
            std::cout <<  result->to_string() << '\n'; 
        } catch (std::string e) {
            std::cerr << e << '\n';
            return 1;
        }

        return 0;
    }
}