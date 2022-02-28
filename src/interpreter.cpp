#include <string>
#include <memory>
#include <cmath>

#include "node.h"
#include "env.h"
#include "entity.h"
#include "concept.h"
#include "builtins.h"
#include "interpreter.h"

namespace pluto
{
    Interpreter::Interpreter(std::string filename)
    {
        this->filename = filename;
    }

    std::unique_ptr<Entity> Interpreter::visit(std::unique_ptr<Node> node, std::unique_ptr<Env> env)
    {
        return visit(node.get(), std::move(env));
    }

    void Interpreter::raise_error(int line, std::string message)
    {
        throw std::string(filename + ":" + std::to_string(line) + ": " + message);
    }

    std::unique_ptr<Entity> Interpreter::visit(Node *node, std::unique_ptr<Env> env)
    {
        switch (node->kind())
        {
        case INT_NODE:
            return visit((IntNode *)node, std::move(env));
        case DOUBLE_NODE:
            return visit((DoubleNode *)node, std::move(env));
        case NAME_NODE:
            return visit((NameNode *)node, std::move(env));
        case TRUE_NODE:
            return visit((TrueNode *)node, std::move(env));
        case FALSE_NODE:
            return visit((FalseNode *)node, std::move(env));
        case NIL_NODE:
            return visit((NilNode *)node, std::move(env));
        case STRING_NODE:
            return visit((StringNode *)node, std::move(env));
        case ADD_NODE:
            return visit((AddNode *)node, std::move(env));
        case SUBTRACT_NODE:
            return visit((SubtractNode *)node, std::move(env));
        case MULTIPLY_NODE:
            return visit((MultiplyNode *)node, std::move(env));
        case DIVIDE_NODE:
            return visit((DivideNode *)node, std::move(env));
        case MOD_NODE:
            return visit((ModNode *)node, std::move(env));
        case OR_NODE:
            return visit((OrNode *)node, std::move(env));
        case AND_NODE:
            return visit((AndNode *)node, std::move(env));
        case XOR_NODE:
            return visit((XorNode *)node, std::move(env));
        case BOR_NODE:
            return visit((BOrNode *)node, std::move(env));
        case BAND_NODE:
            return visit((BAndNode *)node, std::move(env));
        case BXOR_NODE:
            return visit((BXorNode *)node, std::move(env));
        case LSHIFT_NODE:
            return visit((LShiftNode *)node, std::move(env));
        case RSHIFT_NODE:
            return visit((RShiftNode *)node, std::move(env));
        case EE_NODE:
            return visit((EENode *)node, std::move(env));
        case LT_NODE:
            return visit((LTNode *)node, std::move(env));
        case GT_NODE:
            return visit((GTNode *)node, std::move(env));
        case LTE_NODE:
            return visit((LTENode *)node, std::move(env));
        case GTE_NODE:
            return visit((GTENode *)node, std::move(env));
        case PLUS_NODE:
            return visit((PlusNode *)node, std::move(env));
        case MINUS_NODE:
            return visit((MinusNode *)node, std::move(env));
        case NOT_NODE:
            return visit((NotNode *)node, std::move(env));
        case BNOT_NODE:
            return visit((BNotNode *)node, std::move(env));
        default:
            raise_error(node->line, "invalid node");
        }
    }
    
    std::unique_ptr<Entity> Interpreter::visit(IntNode *node, std::unique_ptr<Env> env)
    {
        return std::unique_ptr<Entity>(new Int(node->int_val));
    }

    std::unique_ptr<Entity> Interpreter::visit(DoubleNode *node, std::unique_ptr<Env> env)
    {
        return std::unique_ptr<Entity>(new Double(node->double_val));
    }

    std::unique_ptr<Entity> Interpreter::visit(StringNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Env> string_env = std::move(((Class *)(Builtins::class_string.get()))->env);
        return std::unique_ptr<Entity>(new Object(std::move(string_env), node->string_val));
    }

    std::unique_ptr<Entity> Interpreter::visit(NameNode *node, std::unique_ptr<Env> env)
    {
        if(env->has(node->name)) {
            return env->get(node->name);
        } else {
            raise_error(node->line, "'" + node->name + "' is not defined"); 
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(TrueNode *node, std::unique_ptr<Env> env)
    {
        return std::unique_ptr<Entity>(new Bool(true));
    }

    std::unique_ptr<Entity> Interpreter::visit(FalseNode *node, std::unique_ptr<Env> env)
    {
        return std::unique_ptr<Entity>(new Bool(false));
    }

    std::unique_ptr<Entity> Interpreter::visit(NilNode *node, std::unique_ptr<Env> env)
    {
        return std::unique_ptr<Entity>(new Nil());
    }

    std::unique_ptr<Entity> Interpreter::visit(AddNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val + ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val + ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val + ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val + ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '+'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(SubtractNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val - ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val - ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val - ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val - ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '-'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(MultiplyNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val * ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val * ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val * ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val * ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '*'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(DivideNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val / ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val / ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val / ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val / ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '/'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(ModNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val % ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(std::fmod(((Int *)a.get())->int_val, ((Double *)b.get())->double_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(std::fmod(((Double *)a.get())->double_val, ((Int *)b.get())->int_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(std::fmod(((Double *)a.get())->double_val, ((Double *)b.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '%'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(OrNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == BOOL_ENTITY && b->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val || ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '||'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(AndNode *node, std::unique_ptr<Env> env)
    {
        // std::cout << "    std::unique_ptr<Entity> Interpreter::visit(AndNode *node, std::move(env))" << '\n';
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == BOOL_ENTITY && b->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val && ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '&&'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(XorNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == BOOL_ENTITY && b->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val != ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '^^'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BOrNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val | ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '|'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BAndNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val & ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '&'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BXorNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val ^ ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '^'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(LShiftNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val << ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '<<'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(RShiftNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val >> ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>>'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(EENode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Int *)a.get())->int_val == ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '=='");
        }
    }
    
std::unique_ptr<Entity> Interpreter::visit(NENode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Int *)a.get())->int_val != ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '=='");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(LTNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Int *)a.get())->int_val < ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '<'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(GTNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Int *)a.get())->int_val > ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(LTENode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Int *)a.get())->int_val <= ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '<='");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(GTENode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a), std::move(env));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b), std::move(env));

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Int *)a.get())->int_val >= ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>='");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(PlusNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node), std::move(env));

        if (a->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(+(((Int *)a.get())->int_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(+(((Double *)a.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(MinusNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node), std::move(env));

        if (a->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(-(((Int *)a.get())->int_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(-(((Double *)a.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(NotNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node), std::move(env));

        if (a->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(!(((Bool *)a.get())->bool_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '!'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BNotNode *node, std::unique_ptr<Env> env)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node), std::move(env));

        if (a->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(~(((Int *)a.get())->int_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '~'");
        }
    }
}