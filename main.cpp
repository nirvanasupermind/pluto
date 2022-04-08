#include <iostream>
#include <string>

#include "src/location.cpp"
#include "src/token.cpp"
#include "src/lexer.cpp"

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

            while (true)
            {
                pluto::Token token = lexer.gettok();
                if (token.type == pluto::TokenType::EOF_)
                {
                    break;
                }

                std::cout << token.repr() << '\n';
            }
        }
        catch (const std::string &e)
        {
            std::cerr << e << '\n';
        }
    }
}