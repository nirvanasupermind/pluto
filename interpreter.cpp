#include <string>
#include <cmath>

#include "nodes.h"
#include "values.h"
#include "scopes.h"
#include "interpreter.h"

namespace Interpreter {
    Interpreter::Interpreter(std::string filename) {
        this->filename = filename;
    }

    Values::Value *Interpreter::visit(Nodes::Node *node, Scopes::Scope *scope) {
        // std::cout << node->to_string() << '\n';

        switch (node->node_type) {
            case Nodes::EmptyNode:
                return new Values::Nil();
            case Nodes::ByteNode:
                return new Values::Byte(node->byte);
            case Nodes::NumberNode:
                return new Values::Number(node->value);                
            case Nodes::TrueNode:
                return new Values::Bool(true);
            case Nodes::FalseNode:
                return new Values::Bool(false);
            case Nodes::NilNode:
                return new Values::Nil();
            case Nodes::SymbolNode:
                return visit_symbol_node(node, scope);
            case Nodes::AddNode:
                return visit_add_node(node, scope);
            case Nodes::SubtractNode:
                return visit_subtract_node(node, scope);
            case Nodes::MultiplyNode:
                return visit_multiply_node(node, scope);
            case Nodes::DivideNode:
                return visit_divide_node(node, scope);
            case Nodes::PowerNode:
                return visit_power_node(node, scope);
            case Nodes::PlusNode:
                return visit_plus_node(node, scope);
            case Nodes::MinusNode:
                return visit_minus_node(node, scope);
            case Nodes::FileNode:
                return visit_file_node(node, scope);
            default:
                throw std::string(filename + ":" + std::to_string(node->line) + ": invalid node");
        }
    }

    Values::Value *Interpreter::visit_symbol_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *result = scope->get(node->symbol);

        if(result == nullptr)
            throw std::string(filename + ":" + std::to_string(node->line) + ": cannot find symbol '"+node->symbol+"'");
        
        return result;
    }

    Values::Value *Interpreter::visit_add_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte + ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value + ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '+'");
        }
    }

    Values::Value *Interpreter::visit_subtract_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte - ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value - ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '-'");
        }
    }

    Values::Value *Interpreter::visit_multiply_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte * ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value * ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '*'");
        }
    }

    Values::Value *Interpreter::visit_divide_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte / ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value / ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand type for unary operator '+'");
        }
    }

    Values::Value *Interpreter::visit_plus_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);

        if(INSTANCEOF(a, Values::Byte)) {
            return new Values::Byte(((Values::Byte*)a)->byte);            
        } else if(INSTANCEOF(a, Values::Number)) {
            return new Values::Number(((Values::Number*)a)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand type for unary operator '-'");
        }
    }

    Values::Value *Interpreter::visit_minus_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);

        if(INSTANCEOF(a, Values::Byte)) {
            return new Values::Byte(-((Values::Byte*)a)->byte);            
        } else if(INSTANCEOF(a, Values::Number)) {
            return new Values::Number(-((Values::Number*)a)->value);
        } else {
            throw std::string(filename + std::to_string(node->line) + ": bad operand types for binary operator '**'");
        }
    }

    Values::Value *Interpreter::visit_power_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Number(std::pow(((Values::Number*)a)->value, ((Values::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '**'");
        }
    }

    Values::Value *Interpreter::visit_file_node(Nodes::Node *node, Scopes::Scope *scope) {
        for(int i = 0; i < node->stmts.size() - 1; i++) {
            visit(node->stmts[i], scope);
        }

        return visit(node->stmts.back(), scope);
    }
}