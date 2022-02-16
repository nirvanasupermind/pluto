#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>

#include "token.h"

namespace pluto
{
    enum NodeKind
    {
        INT_NODE,
        DOUBLE_NODE,
        STRING_NODE,
        TRUE_NODE,
        FALSE_NODE,
        ADD_NODE,
        SUBTRACT_NODE,
        MULTIPLY_NODE,
        DIVIDE_NODE,
        MOD_NODE,
        PLUS_NODE,
        MINUS_NODE
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
        int int_val;

        IntNode(int line, int int_val);

        NodeKind kind();

        std::string to_string();
    };

    class DoubleNode : public Node
    {
    public:
        double double_val;        
        
        DoubleNode(int line, double double_val);

        NodeKind kind();

        std::string to_string();
    };

    class StringNode : public Node
    {
    public:
        std::string string_val;

        StringNode(int line, std::string string_val);

        NodeKind kind();

        std::string to_string();
    };

    class TrueNode : public Node
    {
    public:
        TrueNode(int line);

        NodeKind kind();

        std::string to_string();
    };

    class FalseNode : public Node
    {
    public:
        FalseNode(int line);

        NodeKind kind();

        std::string to_string();
    };

    class AddNode : public Node
    {
    public:
        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        AddNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };


    class SubtractNode : public Node
    {
    public:
        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        SubtractNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class MultiplyNode : public Node
    {
    public:
        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        MultiplyNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class DivideNode : public Node
    {
    public:
        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        DivideNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class ModNode : public Node
    {
    public:
        std::unique_ptr<Node> node_a;
        std::unique_ptr<Node> node_b;

        ModNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class PlusNode : public Node
    {
    public:
        std::unique_ptr<Node> node;

        PlusNode(int line, std::unique_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };

    class MinusNode : public Node
    {
    public:
        std::unique_ptr<Node> node;

        MinusNode(int line, std::unique_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };
}

#endif