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
        // std::cout << node->node_type << '\n';

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
            case Nodes::LTNode:
                return visit_lt_node(node, scope);
            case Nodes::GTNode:
                return visit_gt_node(node, scope);
            case Nodes::LENode:
                return visit_le_node(node, scope);
            case Nodes::GENode:
                return visit_ge_node(node, scope);
            case Nodes::EENode:
                return visit_ee_node(node, scope);
            case Nodes::NENode:
                return visit_ne_node(node, scope);
            case Nodes::EQNode:
                return visit_eq_node(node, scope);
            case Nodes::VarNode:
                return visit_var_node(node, scope);
            case Nodes::BlockNode:
                return visit_block_node(node, scope);
            case Nodes::IfNode:
                return visit_if_node(node, scope);
            case Nodes::IfElseNode:
                return visit_if_else_node(node, scope);
            case Nodes::ForNode:
                return visit_for_node(node, scope);
            case Nodes::WhileNode:
                return visit_while_node(node, scope);
            case Nodes::FileNode:
                return visit_file_node(node, scope);
            default:
                throw std::string(filename + ":" + std::to_string(node->line) + ": invalid node");
        }
    }

    Values::Value *Interpreter::visit_symbol_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *result = scope->get(node->symbol);

        if(result == nullptr)
            throw std::string(filename + ":" + std::to_string(node->line) + ": cannot find variable '"+node->symbol+"'");
        
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

    Values::Value *Interpreter::visit_eq_node(Nodes::Node *node, Scopes::Scope *scope) {
        if(node->node_a->node_type != Nodes::SymbolNode)
            throw std::string(filename + ":" + std::to_string(node->line) + ": invalid left-hand side in assignment");
        
        std::string name = node->node_a->symbol;

        if(scope->get(name) == nullptr) {
            throw std::string(filename + ":" + std::to_string(node->line) + ": cannot find variable '" + name + "'");
        }
        
        Values::Value *val = visit(node->node_b, scope);

        scope->resolve(name)->set(name, val);

        return val;
    }

    Values::Value *Interpreter::visit_lt_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Bool(((Values::Byte*)a)->byte < ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Bool(((Values::Number*)a)->value < ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '<'");
        }
    }

    Values::Value *Interpreter::visit_gt_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Bool(((Values::Byte*)a)->byte > ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Bool(((Values::Number*)a)->value > ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '>'");
        }
    }

    Values::Value *Interpreter::visit_le_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Bool(((Values::Byte*)a)->byte <= ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Bool(((Values::Number*)a)->value <= ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '<='");
        }
    }

    Values::Value *Interpreter::visit_ge_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Bool(((Values::Byte*)a)->byte >= ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Bool(((Values::Number*)a)->value >= ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '>='");
        }
    }

    Values::Value *Interpreter::visit_ee_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Bool(((Values::Byte*)a)->byte == ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Bool(((Values::Number*)a)->value == ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '=='");
        }
    }

    Values::Value *Interpreter::visit_ne_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *a = visit(node->node_a, scope);
        Values::Value *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Values::Byte) && INSTANCEOF(b, Values::Byte)) {
            return new Values::Bool(((Values::Byte*)a)->byte != ((Values::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Values::Number) && INSTANCEOF(b, Values::Number)) {
            return new Values::Bool(((Values::Number*)a)->value != ((Values::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '!='");
        }
    }


    Values::Value *Interpreter::visit_var_node(Nodes::Node *node, Scopes::Scope *scope) {

        std::string name = node->name;

        if(scope->map.count(name) != 0)
            throw std::string(filename + ":" + std::to_string(node->line) + ": variable '" + name + "' is already defined");
        
        Values::Value *val = visit(node->val, scope);

        scope->set(name, val);

        return val;
    }

    Values::Value *Interpreter::visit_block_node(Nodes::Node *node, Scopes::Scope *scope) {
        Scopes::Scope *block_scope = new Scopes::Scope(scope);

        if(node->stmts.size() == 0)
            return new Values::Nil();

        for(int i = 0; i < node->stmts.size() - 1; i++) {
            visit(node->stmts[i], block_scope);
        }

        return visit(node->stmts.back(), block_scope);
    }
    
    Values::Value *Interpreter::visit_if_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *cond = visit(node->node_a, scope);

        if(cond->truthy()) {
            visit(node->node_b, scope);
        }
        
        return new Values::Nil();
    }

    Values::Value *Interpreter::visit_if_else_node(Nodes::Node *node, Scopes::Scope *scope) {
        Values::Value *cond = visit(node->node_a, scope);

        if(cond->truthy())
            visit(node->node_b, scope);
        else
            visit(node->node_c, scope);
        
        
        return new Values::Nil();
    }

    Values::Value *Interpreter::visit_for_node(Nodes::Node *node, Scopes::Scope *scope) {
         Scopes::Scope *for_scope = new Scopes::Scope(scope);

        visit(node->node_a, for_scope);

        while(true) {
            if(!(visit(node->node_b, for_scope)->truthy()))
                break;

            visit(node->node_c, for_scope);
            visit(node->node_d, for_scope);
        }
        
        return new Values::Nil();
    }

    Values::Value *Interpreter::visit_while_node(Nodes::Node *node, Scopes::Scope *scope) {
        while(true) {
            if(!(visit(node->node_a, scope)->truthy()))
                break;
            visit(node->node_b, scope);
        }
        
        return new Values::Nil();
    }

    Values::Value *Interpreter::visit_file_node(Nodes::Node *node, Scopes::Scope *scope) {
        if(node->stmts.size() == 0)
            return new Values::Nil();

        for(int i = 0; i < node->stmts.size(); i++) {
            visit(node->stmts[i], scope);
        }

        return visit(node->stmts.back(), scope);
    }
}