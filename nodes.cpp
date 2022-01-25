#include <iostream>
#include <string>

#include "nodes.h"

namespace Nodes {
    Node::Node(int line, NodeType node_type, signed char byte) {
        this->line = line;
        this->node_type = node_type;
        this->byte = byte;
        node_a = nullptr;
        node_b = nullptr;
    }

    Node::Node(int line, NodeType node_type, double value) {
        this->line = line;
        this->node_type = node_type;
        this->value = value;
        node_a = nullptr;
        node_b = nullptr;
    }

    Node::Node(int line, NodeType node_type, bool bool_) {
        this->line = line;
        this->node_type = node_type;
        this->bool_ = bool_;
        node_a = nullptr;
        node_b = nullptr;
    }

    Node::Node(int line, NodeType node_type, Node *node_a, Node *node_b) {
        this->line = line;
        this->node_type = node_type;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    Node::Node(int line, NodeType node_type) {
        this->line = line;
        this->node_type = node_type;
        node_a = nullptr;
        node_b = nullptr;
    }

    Node::Node(int line, NodeType node_type, Node *node_a) {
        this->line = line;
        this->node_type = node_type;
        this->node_a = node_a;
        node_b = nullptr;
    }

    Node::Node(int line, NodeType node_type, std::vector<Node *> stmts) {
        this->line = line;
        this->node_type = node_type;
        this->stmts = stmts;
    }

    std::string Node::to_string() {
        switch (node_type) {
            case ByteNode: return std::to_string((int)byte);
            case NumberNode: return std::to_string(value);
            case TrueNode: return "true";
            case FalseNode: return "false";
            case NameNode: return name;
            case PlusNode: return "(+" + (*node_a).to_string() + ")";
            case MinusNode: return "(-" + (*node_a).to_string() + ")";
            case AddNode: return "(" + (*node_a).to_string() + " + " + (*node_b).to_string() + ")";
            case SubtractNode: return "(" + (*node_a).to_string() + " - " + (*node_b).to_string() + ")";
            case MultiplyNode: return "(" + (*node_a).to_string() + " * " + (*node_b).to_string() + ")";
            case DivideNode: return "(" + (*node_a).to_string() + " / " + (*node_b).to_string() + ")";
            case PowerNode: return "(" + (*node_a).to_string() + " ** " + (*node_b).to_string() + ")";
            case FileNode: return "(file )";
            default: return "()";
        }
    }

    void free_node(Node *node) {
        if (node == nullptr) {
            // std::cout << "node inside free_node null" << '\n';

            return;

        }


        for (int i = 0; i < node->stmts.size(); i++) {
            free_node(node->stmts[i]);
        }       

        if (node->node_a != nullptr) {
            free_node(node->node_a);

            node->node_a = nullptr;
        }

        if (node->node_b != nullptr) {
            free_node(node->node_b);
            node->node_b = nullptr;
        }

        delete node;
    }
}