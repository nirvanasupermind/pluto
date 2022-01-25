#include <string>
#include <cmath>

#include "nodes.h"
#include "values.h"
#include "interpreter.h"

namespace Interpreter {
    Interpreter::Interpreter(std::string filename) {
        this->filename = filename;
    }

    Values::Value *Interpreter::visit(Nodes::Node *node) {
        // std::cout << node->to_string() << '\n';

        switch (node->node_type) {
            case Nodes::EmptyNode:
                return new Values::Nil();
            case Nodes::ByteNode:
                return new Values::Byte(node->byte);
            case Nodes::NumberNode:
                return new Values::Number(node->value);
            case Nodes::BoolNode:
                return new Values::Bool(node->bool_);
            case Nodes::AddNode:
                return visit_add_node(node);
            case Nodes::SubtractNode:
                return visit_subtract_node(node);
            case Nodes::MultiplyNode:
                return visit_multiply_node(node);
            case Nodes::DivideNode:
                return visit_divide_node(node);
            case Nodes::PowerNode:
                return visit_power_node(node);
            case Nodes::PlusNode:
                return visit_plus_node(node);
            case Nodes::MinusNode:
                return visit_minus_node(node);
            case Nodes::FileNode:
                return visit_file_node(node);
            default:
                throw std::string(filename + ":" + std::to_string(node->line) + ": invalid node");
        }
    }

    Values::Value *Interpreter::visit_add_node(Nodes::Node *node) {
        Values::Value *a = visit(node->node_a);
        Values::Value *b = visit(node->node_b);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte + ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value + ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '+'");
        }
    }

    Values::Value *Interpreter::visit_subtract_node(Nodes::Node *node) {
        Values::Value *a = visit(node->node_a);
        Values::Value *b = visit(node->node_b);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte - ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value - ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '-'");
        }
    }

    Values::Value *Interpreter::visit_multiply_node(Nodes::Node *node) {
        Values::Value *a = visit(node->node_a);
        Values::Value *b = visit(node->node_b);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte * ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value * ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '*'");
        }
    }

    Values::Value *Interpreter::visit_divide_node(Nodes::Node *node) {
        Values::Value *a = visit(node->node_a);
        Values::Value *b = visit(node->node_b);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte / ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value / ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand type for unary operator '+'");
        }
    }

    Values::Value *Interpreter::visit_plus_node(Nodes::Node *node) {
        Values::Value *a = visit(node->node_a);

        if(INSTANCEOF(a, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte);            
        } else if(INSTANCEOF(a, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand type for unary operator '-'");
        }
    }

    Values::Value *Interpreter::visit_minus_node(Nodes::Node *node) {
        Values::Value *a = visit(node->node_a);

        if(INSTANCEOF(a, Values::Byte)) {
            return new Values::Byte(-((Values::Byte*)a)->byte);            
        } else if(INSTANCEOF(a, Values::Number)) {
            return new Values::Number(-((Values::Number*)a)->value);
        } else {
            throw std::string(filename + std::to_string(node->line) + ": bad operand types for binary operator '**'");
        }
    }

    Values::Value *Interpreter::visit_power_node(Nodes::Node *node) {
        Values::Value *a = visit(node->node_a);
        Values::Value *b = visit(node->node_b);

        if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(std::pow(((Values::Number*)a)->value, ((Values::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '**'");
        }
    }

    Values::Value *Interpreter::visit_file_node(Nodes::Node *node) {
        for(int i = 0; i < node->stmts.size() - 1; i++) {
            visit(node->stmts[i]);
        }

        return visit(node->stmts.back());
    }
}