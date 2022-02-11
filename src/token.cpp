#include <string>

#include "token.h"

namespace pluto
{
    Token::Token(int ln, TokenType type)
    {
        this.ln = ln;
        this.type = type;
    }

    Token::Token(int ln, TokenType type, double num_val)
    {
        this.ln = ln;
        this.type = type;
        this.num_val = num_val;
    }
}
