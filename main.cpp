#include <iostream>
#include <string>

#include "tokens.cpp"
#include "lexer.cpp"
#include "nodes.cpp"
#include "parser.cpp"
#include "values.cpp"
#include "interpreter.cpp"

int main()
{
    std::string text;

    while (true)
    {
        try
        {
            std::cout << "pluto > " << std::flush;
            std::getline(std::cin, text);

            if (std::cin.bad())
            {
                std::cerr << "IO error\n";
                break;
            }
            else if (std::cin.eof())
            {
                break;
            }

            pluto::Lexer lexer(text);
            std::vector<pluto::Token> tokens = lexer.generate_tokens();

            // pluto::print_tokens(tokens);

            pluto::Parser parser(tokens);
            std::shared_ptr<pluto::Node> tree = parser.parse();

            if (!tree)
            {
                continue;
            }

            // std::cout << tree->str() << '\n';

            pluto::Interpreter interpreter;
            pluto::Number value = interpreter.visit(tree);

            std::cout << value.str() << '\n';
        }
        catch (const std::string &e)
        {
            std::cerr << e << '\n';
        }
    }
}