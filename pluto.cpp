#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <string_view>
#include <sstream>
#include "src/lexer.hpp"

//https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
std::string file_to_string(const std::string& file_name)
{
    std::ifstream file_stream(file_name);

    if (file_stream.fail())
    {
        // Error opening file.
    }

    std::ostringstream str_stream;
    file_stream >> str_stream.rdbuf();  // NOT str_stream << file_stream.rdbuf()

    if (file_stream.fail() && !file_stream.eof())
    {
        // Error reading file.
    }

    return str_stream.str();
}

int main(int argc, char *argv[]) {
    if(argc >= 2) {
        std::string path(argv[1]);

        std::string input = file_to_string(path);

        pluto::Lexer lexer(input);
        lexer.tokenizer();

        for(int i = 0; i < lexer.tokens.size(); i++) {
            std::cout << static_cast<std::string>(lexer.tokens[i]) + "\n";
        }
    }
}