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

    void Interpreter::raise_error(int line, std::string message)
    {
        throw std::string(filename + ":" + std::to_string(line) + ": " + message);
    }

    std::shared_ptr<Entity> Interpreter::visit(std::shared_ptr<Node> node, std::shared_ptr<Env> env)
    {
        return visit(node.get(), env);
    }

    std::shared_ptr<Entity> Interpreter::visit(Node *node, std::shared_ptr<Env> env)
    {
        switch (node->kind())
        {
        case PROGRAM_NODE:
            return visit((ProgramNode *)node, env);
        case INT_NODE:
            return visit((IntNode *)node, env);
        case DOUBLE_NODE:
            return visit((DoubleNode *)node, env);
        case NAME_NODE:
            return visit((NameNode *)node, env);
        case TRUE_NODE:
            return visit((TrueNode *)node, env);
        case FALSE_NODE:
            return visit((FalseNode *)node, env);
        case NIL_NODE:
            return visit((NilNode *)node, env);
        case STRING_NODE:
            return visit((StringNode *)node, env);
        case ADD_NODE:
            return visit((AddNode *)node, env);
        case SUBTRACT_NODE:
            return visit((SubtractNode *)node, env);
        case MULTIPLY_NODE:
            return visit((MultiplyNode *)node, env);
        case DIVIDE_NODE:
            return visit((DivideNode *)node, env);
        case MOD_NODE:
            return visit((ModNode *)node, env);
        case OR_NODE:
            return visit((OrNode *)node, env);
        case AND_NODE:
            return visit((AndNode *)node, env);
        case XOR_NODE:
            return visit((XorNode *)node, env);
        case BOR_NODE:
            return visit((BOrNode *)node, env);
        case BAND_NODE:
            return visit((BAndNode *)node, env);
        case BXOR_NODE:
            return visit((BXorNode *)node, env);
        case LSHIFT_NODE:
            return visit((LShiftNode *)node, env);
        case RSHIFT_NODE:
            return visit((RShiftNode *)node, env);
        case EE_NODE:
            return visit((EENode *)node, env);
        case LT_NODE:
            return visit((LTNode *)node, env);
        case GT_NODE:
            return visit((GTNode *)node, env);
        case LTE_NODE:
            return visit((LTENode *)node, env);
        case GTE_NODE:
            return visit((GTENode *)node, env);
        case PLUS_NODE:
            return visit((PlusNode *)node, env);
        case MINUS_NODE:
            return visit((MinusNode *)node, env);
        case NOT_NODE:
            return visit((NotNode *)node, env);
        case BNOT_NODE:
            return visit((BNotNode *)node, env);
        default:
            raise_error(node->line, "invalid node");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(ProgramNode *node, std::shared_ptr<Env> env)
    {
        for(int i = 0; i < node->nodes.size() - 1; i++) {
            visit(node->nodes.at(i), env);
        }

        return std::shared_ptr<Entity>(visit(node->nodes.back(), env));
    }

    std::shared_ptr<Entity> Interpreter::visit(IntNode *node, std::shared_ptr<Env> env)
    {
        return std::shared_ptr<Entity>(new Int(node->int_val));
    }

    std::shared_ptr<Entity> Interpreter::visit(DoubleNode *node, std::shared_ptr<Env> env)
    {
        return std::shared_ptr<Entity>(new Double(node->double_val));
    }

    std::shared_ptr<Entity> Interpreter::visit(StringNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Env> string_env = ((Class *)(Builtins::class_string.get()))->env;
        return std::shared_ptr<Entity>(new Object(string_env));
    }

    std::shared_ptr<Entity> Interpreter::visit(NameNode *node, std::shared_ptr<Env> env)
    {
        if(env->has(node->name)) {
            return env->get(node->name);
        } else {
            raise_error(node->line, "'" + node->name + "' is not defined"); 
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(TrueNode *node, std::shared_ptr<Env> env)
    {
        return std::shared_ptr<Entity>(new Bool(true));
    }

    std::shared_ptr<Entity> Interpreter::visit(FalseNode *node, std::shared_ptr<Env> env)
    {
        return std::shared_ptr<Entity>(new Bool(false));
    }

    std::shared_ptr<Entity> Interpreter::visit(NilNode *node, std::shared_ptr<Env> env)
    {
        return std::shared_ptr<Entity>(new Nil());
    }

    std::shared_ptr<Entity> Interpreter::visit(AddNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val + ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Int *)a.get())->int_val + ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val + ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val + ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '+'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(SubtractNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val - ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Int *)a.get())->int_val - ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val - ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val - ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '-'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(MultiplyNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val * ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Int *)a.get())->int_val * ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val * ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val * ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '*'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(DivideNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val / ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Int *)a.get())->int_val / ((Double *)b.get())->double_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val / ((Int *)b.get())->int_val));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(((Double *)a.get())->double_val / ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '/'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(ModNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val % ((Int *)b.get())->int_val));
        }
        else if (a->kind() == INT_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::fmod(((Int *)a.get())->int_val, ((Double *)b.get())->double_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::fmod(((Double *)a.get())->double_val, ((Int *)b.get())->int_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY && b->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::fmod(((Double *)a.get())->double_val, ((Double *)b.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '%'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(OrNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == BOOL_ENTITY && b->kind() == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val || ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '||'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(AndNode *node, std::shared_ptr<Env> env)
    {
        // std::cout << "    std::shared_ptr<Entity> Interpreter::visit(AndNode *node, env)" << '\n';
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == BOOL_ENTITY && b->kind() == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val && ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '&&'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(XorNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == BOOL_ENTITY && b->kind() == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val != ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '^^'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(BOrNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val | ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '|'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(BAndNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val & ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '&'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(BXorNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val ^ ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '^'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(LShiftNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val << ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '<<'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(RShiftNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(((Int *)a.get())->int_val >> ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>>'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(EENode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Int *)a.get())->int_val == ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '=='");
        }
    }
    
std::shared_ptr<Entity> Interpreter::visit(NENode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Int *)a.get())->int_val != ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '=='");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(LTNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Int *)a.get())->int_val < ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '<'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(GTNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Int *)a.get())->int_val > ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(LTENode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Int *)a.get())->int_val <= ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '<='");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(GTENode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        if (a->kind() == INT_ENTITY && b->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(((Int *)a.get())->int_val >= ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>='");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(PlusNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        if (a->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(+(((Int *)a.get())->int_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(+(((Double *)a.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(MinusNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        if (a->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(-(((Int *)a.get())->int_val)));
        }
        else if (a->kind() == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(-(((Double *)a.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(NotNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        if (a->kind() == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(!(((Bool *)a.get())->bool_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '!'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(BNotNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        if (a->kind() == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(~(((Int *)a.get())->int_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '~'");
        }
    }
}