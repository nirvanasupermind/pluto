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

    class IntNode : public Node
    {
    public:
        int line;

        int int_val;

        IntNode(int line, int int_val);

        std::string to_string();
    };

    class DoubleNode : public Node
    {
    public:
        int line;

        double double_val;

        DoubleNode(int line, double double_val);

        std::string to_string();
    };

}

#endif