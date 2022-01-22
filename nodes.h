#ifndef NODES_H
#define NODES_H

#include <string>

namespace Nodes {
    enum NodeType {
        PlusNode,
        MinusNode,
        EmptyNode,
        ByteNode,
        NumberNode,
        AddNode,
        SubtractNode,
        MultiplyNode,
        DivideNode,
        PowerNode
    };

    class Node {
        public:
            int line;
            NodeType node_type;
            signed char byte;
            double value;
            Node *node_a;
            Node *node_b;

            Node(int, NodeType, signed char byte);
            Node(int, NodeType, double value);
            Node(int, NodeType, Node *, Node *);
            Node(int, NodeType);
            Node(int, NodeType, Node *);

            operator std::string const();
    };

    void print_node(Node *);
    void free_node(Node *);
}

#endif // NODES_H