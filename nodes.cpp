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
    }

    Node::Node(int line, NodeType node_type, Node *node_a, Node *node_b) {
        this->line = line;
        this->node_type = node_type;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    Node::Node(int line, NodeType node_type, Node *node_a, Node *node_b, Node *node_c) {
        this->line = line;
        this->node_type = node_type;
        this->node_a = node_a;
        this->node_b = node_b;
        this->node_c = node_c;
    }

    Node::Node(int line, NodeType node_type, Node *node_a, Node *node_b, Node *node_c, Node *node_d) {
        this->line = line;
        this->node_type = node_type;
        this->node_a = node_a;
        this->node_b = node_b;
        this->node_c = node_c;
        this->node_d = node_d;
    }

    Node::Node(int line, NodeType node_type) {
        this->line = line;
        this->node_type = node_type;
    }

    Node::Node(int line, NodeType node_type, Node *node_a) {
        this->line = line;
        this->node_type = node_type;
        this->node_a = node_a;
    }

    Node::Node(int line, NodeType node_type, std::string symbol) {
        this->line = line;
        this->node_type = node_type;
        this->symbol = symbol;
    }

    Node::Node(int line, NodeType node_type, std::string name, Node *val) {
        this->line = line;
        this->node_type = node_type;
        this->name = name;
        this->val = val;
    }

    Node::Node(int line, NodeType node_type, std::string name, std::vector<std::string> args, Node *body) {
        this->line = line;
        this->name = name;
        this->args = args;
        this->body = body;
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
            case NilNode: return "nil";
            case SymbolNode: return symbol;
            case PlusNode: return "(+ " + node_a->to_string() + ")";
            case MinusNode: return "(-" + node_a->to_string() + ")";
            case AddNode: return "(" + node_a->to_string() + " + " + node_b->to_string() + ")";
            case SubtractNode: return "(" + node_a->to_string() + " - " + node_b->to_string() + ")";
            case MultiplyNode: return "(" + node_a->to_string() + " * " + node_b->to_string() + ")";
            case DivideNode: return "(" + node_a->to_string() + " / " + node_b->to_string() + ")";
            case PowerNode: return "(" + node_a->to_string() + " ** " + node_b->to_string() + ")";
            case FileNode: { 
                std::string result("(");
                for(int i = 0; i < stmts.size(); i++) {
                    result = result + stmts[i]->to_string();
                }

                result = result + ")";
                
                return "(file)";
            }
            default: return "()";
        }
    }

    void free_node(Node *node) {
        if (node == nullptr) {
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

        if (node->node_c != nullptr) {
            free_node(node->node_c);
            node->node_c = nullptr;
        }

        delete node;
    }
}