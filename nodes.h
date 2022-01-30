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
        NilNode,
        SymbolNode,
        AddNode,
        SubtractNode,
        MultiplyNode,
        DivideNode,
        PowerNode,
        LTNode,
        GTNode,
        LENode,
        GENode,
        EENode,
        NENode,
        EQNode,
        ReturnNode,
        VarNode,
        BlockNode,
        IfNode,
        IfElseNode,
        WhileNode,
        FileNode
    };

    class Node {
        public:
            int line;
            NodeType node_type;
            signed char byte;
            double value;
            std::string symbol;
            
            std::string name;
            Node *val;

            Node *node_a;
            Node *node_b;
            Node *node_c;
            std::vector<Node *> stmts;

            Node(int, NodeType, signed char byte);
            Node(int, NodeType, double value);
            Node(int, NodeType, std::string);
            Node(int, NodeType, Node *, Node *);
            Node(int, NodeType, Node *, Node *, Node *);
            Node(int, NodeType);
            Node(int, NodeType, Node *);
            Node(int, NodeType, std::string, Node *);
            Node(int, NodeType, std::vector<Node *>);

            std::string to_string();
    };

    void free_node(Node *);
}

#endif // NODES_H