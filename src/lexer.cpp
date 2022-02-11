#include <string>
#include <vector>

#include "token.h"
#include "lexer.h"

namespace pluto
{
    Lexer::Lexer(std::string filename, std::string text) {
        this->filename = filename;
        this->text = text;
        idx = 0;
        ln = 1;
    }
}