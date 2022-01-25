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
        TrueNode,
        FalseNode,
        NameNode,
        AddNode,
        SubtractNode,
        MultiplyNode,
        DivideNode,
        PowerNode,
        FileNode
    };

    class Node {
        public:
            int line;
            NodeType node_type;
            signed char byte;
            double value;
            std::string name;
            Node *node_a;
            Node *node_b;
            std::vector<Node *> stmts;

            Node(int, NodeType, signed char byte);
            Node(int, NodeType, double value);
            Node(int, NodeType, std::string name);
            Node(int, NodeType, Node *, Node *);
            Node(int, NodeType);
            Node(int, NodeType, Node *);
            Node(int, NodeType, std::vector<Node *>);

            std::string to_string();
    };

    void free_node(Node *);
}

#endif // NODES_H