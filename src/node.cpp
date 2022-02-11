#include <string>

#include "node.h"

namespace pluto
{
    StringNode::StringNode(int line, std::string string_val)
    {
        this->line = line;
        this->string_val = string_val;
    }

    std::string StringNode::to_string()
    {
        return string_val;
    }

    IntNode::IntNode(int line, int int_Val)
    {
        this->line = line;
        this->int_val = int_val;
    }

    std::string IntNode::to_string()
    {
        return std::to_string(int_val);
    }

    DoubleNode::DoubleNode(int line, double double_val)
    {
        this->line = line;
        this->double_val = double_val;
    }

    std::string DoubleNode::to_string()
    {
        return std::to_string(double_val);
    }
}