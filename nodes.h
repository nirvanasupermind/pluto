#ifndef NODES_H
#define NODES_H

#include <string>
#include <memory>

namespace pluto
{

    enum class NodeKind
    {
        Number,
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
        virtual NodeKind kind() const = 0;
        virtual std::string str() const = 0;
        virtual ~Node() = default;
    };

    class NumberNode : public Node
    {
    public:
        double value;

        explicit NumberNode(double value);
        NodeKind kind() const;
        std::string str() const;
    };

    class AddNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        explicit AddNode(std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);
        NodeKind kind() const;
        std::string str() const;
    };

    class SubtractNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        explicit SubtractNode(std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);
        NodeKind kind() const;
        std::string str() const;
    };

    class MultiplyNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        explicit MultiplyNode(std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);
        NodeKind kind() const;
        std::string str() const;
    };

    class DivideNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        explicit DivideNode(std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);
        NodeKind kind() const;
        std::string str() const;
    };

    class PlusNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        explicit PlusNode(std::shared_ptr<Node> node);

        NodeKind kind() const;
        std::string str() const;
    };

    class MinusNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        explicit MinusNode(std::shared_ptr<Node> node);
        NodeKind kind() const;
        std::string str() const;
    };

} // namespace pluto

#endif // NODES_H