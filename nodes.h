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
        OrNode,
        AndNode,
        XorNode,
        NotNode,
        BitOrNode,
        BitAndNode,
        BitXorNode,
        BitNotNode,
        LshiftNode,
        RshiftNode,
        VarNode,
        BlockNode,
        IfNode,
        IfElseNode,
        ForNode,
        WhileNode,
        FunctionNode,
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

            Node *node_a = nullptr;
            Node *node_b = nullptr;
            Node *node_c = nullptr;
            Node *node_d = nullptr;
            std::vector<Node *> stmts;
            
            std::vector<std::string> args;
            Node *body = nullptr;

            Node(int, NodeType, signed char byte);
            Node(int, NodeType, double value);
            Node(int, NodeType, std::string);
            Node(int, NodeType, Node *, Node *);
            Node(int, NodeType, Node *, Node *, Node *);
            Node(int, NodeType, Node *, Node *, Node *, Node *);
            Node(int, NodeType);
            Node(int, NodeType, Node *);
            Node(int, NodeType, std::string, Node *);
            Node(int, NodeType, std::string, std::vector<std::string>, Node *);
            Node(int, NodeType, std::vector<Node *>);

            std::string to_string();
    };

    void free_node(Node *);
}

#endif // NODES_H