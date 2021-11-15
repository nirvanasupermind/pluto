#include <iostream>
#include "src/lexer.hpp"

std::string readAllText(std::string const &path) {
    assert(path.c_str() != NULL);
    FILE *stream = fopen(path.c_str(), "r");
    assert(stream != NULL);
    fseek(stream, 0, SEEK_END);
    long stream_size = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    void *buffer = malloc(stream_size);
    fread(buffer, stream_size, 1, stream);
    assert(ferror(stream) == 0);
    fclose(stream);
    std::string text((const char *)buffer, stream_size);
    assert(buffer != NULL);
    free((void *)buffer);
    return text;
}

int main(int argc, char *argv[]) {
    std::cout << "pls";

    if(argc >= 1) {
        std::string path(argv[1]);
        std::string text = readAllText(path);  
        // std::cout << text;      
        pluto::Lexer lexer(path, text);
        std::vector<pluto::Token> tokens = lexer.get_tokens();

        std::cout << "tokens:";

        for(int i = 0; i < tokens.size(); i++) {
            std::cout << static_cast<std::string>(tokens.at(i));
        }
    }
}