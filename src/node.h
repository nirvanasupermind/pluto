#ifndef NODE_H
#define NODE_H

#include <string>

namespace pluto
{
    class Node
    {
    public:
        int line;

        virtual std::string to_string();
    };

    class StringNode : public Node
    {
    public:
        int line;

        std::string string_val;

        StringNode(int line, std::string string_val);

        std::string to_string();
    };

    class NumberNode : public Node
    {
    public:
        int line;

        double num_val;

        NumberNode(int line, double num_val);

        std::string to_string();
    };
}

#endif