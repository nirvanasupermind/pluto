#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>

#include "token.h"

namespace pluto
{
    enum NodeKind
    {
        Int,
        Double,
        String,
        Add,
        Subtract,
        Multiply,
        Divide,
        Plus,
        Minus
    };

    class Node
    {
    public:
        int line;

        virtual NodeKind kind() = 0;
        
        virtual std::string to_string() = 0;
    };

    class IntNode : public Node
    {
    public:
        int line;

        int int_val;

        IntNode(int line, int int_val);

        NodeKind kind();

        std::string to_string();
    };

    class DoubleNode : public Node
    {
    public:
        int line;

        double double_val;

        DoubleNode(int line, double double_val);

        NodeKind kind();

        std::string to_string();
    };

    class StringNode : public Node
    {
    public:
        int line;

        std::string string_val;

        StringNode(int line, std::string string_val);

        NodeKind kind();

        std::string to_string();
    };

    class AddNode : public Node
    {
    public:
        int line;

        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        AddNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };


    class SubtractNode : public Node
    {
    public:
        int line;

        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        SubtractNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class MultiplyNode : public Node
    {
    public:
        int line;

        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        MultiplyNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class DivideNode : public Node
    {
    public:
        int line;

        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        DivideNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };
}

#endif