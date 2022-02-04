#include <string>
#include <cmath>

#include "nodes.h"
#include "entities.h"
#include "scopes.h"
#include "interpreter.h"

namespace Interpreter {
    Interpreter::Interpreter(std::string filename) {
        this->filename = filename;
    }

    Entities::Entity *Interpreter::visit(Nodes::Node *node, Scopes::Scope *scope) {
        // std::cout << node->node_type << '\n';

        switch (node->node_type) {
            case Nodes::EmptyNode:
                return new Entities::Nil();
            case Nodes::ByteNode:
                return new Entities::Byte(node->byte);
            case Nodes::NumberNode:
                return new Entities::Number(node->value);                
            case Nodes::TrueNode:
                return new Entities::Bool(true);
            case Nodes::FalseNode:
                return new Entities::Bool(false);
            case Nodes::NilNode:
                return new Entities::Nil();
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
            case Nodes::OrNode:
                return visit_or_node(node, scope);
            case Nodes::AndNode:
                return visit_and_node(node, scope);
            case Nodes::XorNode:
                return visit_xor_node(node, scope);
            case Nodes::NotNode:
                return visit_not_node(node, scope);
            case Nodes::BitOrNode:
                return visit_bitor_node(node, scope);
            case Nodes::BitAndNode:
                return visit_bitand_node(node, scope);
            case Nodes::BitXorNode:
                return visit_bitxor_node(node, scope);
            case Nodes::BitNotNode:
                return visit_bitnot_node(node, scope);
            case Nodes::LshiftNode:
                return visit_lshift_node(node, scope);
            case Nodes::RshiftNode:
                return visit_rshift_node(node, scope);
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

    Entities::Entity *Interpreter::visit_symbol_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *result = scope->get(node->symbol);

        if(result == nullptr)
            throw std::string(filename + ":" + std::to_string(node->line) + ": cannot find variable '"+node->symbol+"'");
        
        return result;
    }

    Entities::Entity *Interpreter::visit_add_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte + ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number(((Entities::Number*)a)->value + ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '+'");
        }
    }

    Entities::Entity *Interpreter::visit_subtract_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte - ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number(((Entities::Number*)a)->value - ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '-'");
        }
    }

    Entities::Entity *Interpreter::visit_multiply_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte * ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number(((Entities::Number*)a)->value * ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '*'");
        }
    }

    Entities::Entity *Interpreter::visit_divide_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte / ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number(((Entities::Number*)a)->value / ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand type for unary operator '+'");
        }
    }

    Entities::Entity *Interpreter::visit_plus_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);

        if(INSTANCEOF(a, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte);            
        } else if(INSTANCEOF(a, Entities::Number)) {
            return new Entities::Number(((Entities::Number*)a)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand type for unary operator '-'");
        }
    }

    Entities::Entity *Interpreter::visit_minus_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);

        if(INSTANCEOF(a, Entities::Byte)) {
            return new Entities::Byte(-((Entities::Byte*)a)->byte);            
        } else if(INSTANCEOF(a, Entities::Number)) {
            return new Entities::Number(-((Entities::Number*)a)->value);
        } else {
            throw std::string(filename + std::to_string(node->line) + ": bad operand types for binary operator '**'");
        }
    }

    Entities::Entity *Interpreter::visit_power_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number(std::pow(((Entities::Number*)a)->value, ((Entities::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '**'");
        }
    }

    Entities::Entity *Interpreter::visit_eq_node(Nodes::Node *node, Scopes::Scope *scope) {
        if(node->node_a->node_type != Nodes::SymbolNode)
            throw std::string(filename + ":" + std::to_string(node->line) + ": invalid left-hand side in assignment");
        
        std::string name = node->node_a->symbol;

        if(scope->get(name) == nullptr) {
            throw std::string(filename + ":" + std::to_string(node->line) + ": cannot find variable '" + name + "'");
        }
        
        Entities::Entity *val = visit(node->node_b, scope);

        scope->resolve(name)->set(name, val);

        return val;
    }

    Entities::Entity *Interpreter::visit_lt_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Bool(((Entities::Byte*)a)->byte < ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Bool(((Entities::Number*)a)->value < ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '<'");
        }
    }

    Entities::Entity *Interpreter::visit_gt_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Bool(((Entities::Byte*)a)->byte > ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Bool(((Entities::Number*)a)->value > ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '>'");
        }
    }

    Entities::Entity *Interpreter::visit_le_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Bool(((Entities::Byte*)a)->byte <= ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Bool(((Entities::Number*)a)->value <= ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '<='");
        }
    }

    Entities::Entity *Interpreter::visit_ge_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Bool(((Entities::Byte*)a)->byte >= ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Bool(((Entities::Number*)a)->value >= ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '>='");
        }
    }

    Entities::Entity *Interpreter::visit_ee_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Bool(((Entities::Byte*)a)->byte == ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Bool(((Entities::Number*)a)->value == ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '=='");
        }
    }

    Entities::Entity *Interpreter::visit_ne_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Bool(((Entities::Byte*)a)->byte != ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Bool(((Entities::Number*)a)->value != ((Entities::Number*)b)->value);
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '!='");
        }
    }

    Entities::Entity *Interpreter::visit_or_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        return new Entities::Bool(a->truthy() || b->truthy());            
    }

    Entities::Entity *Interpreter::visit_and_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        return new Entities::Bool(a->truthy() && b->truthy());
    }

    Entities::Entity *Interpreter::visit_xor_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        return new Entities::Bool(a->truthy() != b->truthy());
    }

    Entities::Entity *Interpreter::visit_not_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);

        return new Entities::Bool(!a->truthy());
    }

    Entities::Entity *Interpreter::visit_bitor_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte | ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number((int)(((Entities::Number*)a)->value) | (int)(((Entities::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '|'");
        }
    }
    
    Entities::Entity *Interpreter::visit_bitand_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte & ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number((int)(((Entities::Number*)a)->value) & (int)(((Entities::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '&'");
        }
    }
        
    Entities::Entity *Interpreter::visit_bitxor_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte ^ ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number((int)(((Entities::Number*)a)->value) ^ (int)(((Entities::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '^'");
        }
    }
    
    Entities::Entity *Interpreter::visit_bitnot_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        if(INSTANCEOF(a, Entities::Byte)) {
            return new Entities::Byte(~(((Entities::Byte*)a)->byte));
        } else if(INSTANCEOF(a, Entities::Number)) {
            return new Entities::Number(~((int)(((Entities::Number*)a)->value)));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for unary operator '~'");
        }
    }
    
    Entities::Entity *Interpreter::visit_lshift_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte << ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number((int)(((Entities::Number*)a)->value) << (int)(((Entities::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '^'");
        }
    }

    Entities::Entity *Interpreter::visit_rshift_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *a = visit(node->node_a, scope);
        Entities::Entity *b = visit(node->node_b, scope);

        if(INSTANCEOF(a, Entities::Byte) && INSTANCEOF(b, Entities::Byte)) {
            return new Entities::Byte(((Entities::Byte*)a)->byte >> ((Entities::Byte*)b)->byte);            
        } else if(INSTANCEOF(a, Entities::Number) && INSTANCEOF(b, Entities::Number)) {
            return new Entities::Number((int)(((Entities::Number*)a)->value) >> (int)(((Entities::Number*)b)->value));
        } else {
            throw std::string(filename + ":" + std::to_string(node->line) + ": bad operand types for binary operator '^'");
        }
    }

    Entities::Entity *Interpreter::visit_var_node(Nodes::Node *node, Scopes::Scope *scope) {

        std::string name = node->name;

        if(scope->map.count(name) != 0)
            throw std::string(filename + ":" + std::to_string(node->line) + ": variable '" + name + "' is already defined");
        
        Entities::Entity *val = visit(node->val, scope);

        scope->set(name, val);

        return val;
    }

    Entities::Entity *Interpreter::visit_block_node(Nodes::Node *node, Scopes::Scope *scope) {
        Scopes::Scope *block_scope = new Scopes::Scope(scope);

        if(node->stmts.size() == 0)
            return new Entities::Nil();

        for(int i = 0; i < node->stmts.size() - 1; i++) {
            visit(node->stmts[i], block_scope);
        }

        return visit(node->stmts.back(), block_scope);
    }
    
    Entities::Entity *Interpreter::visit_if_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *cond = visit(node->node_a, scope);

        if(cond->truthy()) {
            visit(node->node_b, scope);
        }
        
        return new Entities::Nil();
    }

    Entities::Entity *Interpreter::visit_if_else_node(Nodes::Node *node, Scopes::Scope *scope) {
        Entities::Entity *cond = visit(node->node_a, scope);

        if(cond->truthy())
            visit(node->node_b, scope);
        else
            visit(node->node_c, scope);
        
        
        return new Entities::Nil();
    }

    Entities::Entity *Interpreter::visit_for_node(Nodes::Node *node, Scopes::Scope *scope) {
         Scopes::Scope *for_scope = new Scopes::Scope(scope);

        visit(node->node_a, for_scope);

        while(true) {
            if(!(visit(node->node_b, for_scope)->truthy()))
                break;

            visit(node->node_c, for_scope);
            visit(node->node_d, for_scope);
        }
        
        return new Entities::Nil();
    }

    Entities::Entity *Interpreter::visit_while_node(Nodes::Node *node, Scopes::Scope *scope) {
        while(true) {
            if(!(visit(node->node_a, scope)->truthy()))
                break;
            visit(node->node_b, scope);
        }
        
        return new Entities::Nil();
    }

    Entities::Entity *Interpreter::visit_file_node(Nodes::Node *node, Scopes::Scope *scope) {
        if(node->stmts.size() == 0)
            return new Entities::Nil();

        for(int i = 0; i < node->stmts.size(); i++) {
            visit(node->stmts[i], scope);
        }

        return visit(node->stmts.back(), scope);
    }
}