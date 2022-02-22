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

    std::unique_ptr<Entity> Interpreter::visit(std::unique_ptr<Node> node)
    {
        return visit(node.get());
    }

    void Interpreter::raise_error(int line, std::string message)
    {
        throw std::string(filename + ":" + std::to_string(line) + ": " + message);
    }

    std::unique_ptr<Entity> Interpreter::visit(Node *node)
    {
        switch (node->kind())
        {
        case INT_NODE:
            return visit((IntNode *)node);
        case DOUBLE_NODE:
            return visit((DoubleNode *)node);
        case TRUE_NODE:
            return visit((TrueNode *)node);
        case FALSE_NODE:
            return visit((FalseNode *)node);
        case NIL_NODE:
            return visit((NilNode *)node);
        case STRING_NODE:
            return visit((StringNode *)node);
        case ADD_NODE:
            return visit((AddNode *)node);
        case SUBTRACT_NODE:
            return visit((SubtractNode *)node);
        case MULTIPLY_NODE:
            return visit((MultiplyNode *)node);
        case DIVIDE_NODE:
            return visit((DivideNode *)node);
        case MOD_NODE:
            return visit((ModNode *)node);
        case OR_NODE:
            return visit((OrNode *)node);
        case AND_NODE:
            return visit((AndNode *)node);
        case XOR_NODE:
            return visit((XorNode *)node);
        case BOR_NODE:
            return visit((BOrNode *)node);
        case BAND_NODE:
            return visit((BAndNode *)node);
        case BXOR_NODE:
            return visit((BXorNode *)node);
        case LSHIFT_NODE:
            return visit((LShiftNode *)node);
        case RSHIFT_NODE:
            return visit((RShiftNode *)node);
        case PLUS_NODE:
            return visit((PlusNode *)node);
        case MINUS_NODE:
            return visit((MinusNode *)node);
        case NOT_NODE:
            return visit((NotNode *)node);
        case BNOT_NODE:
            return visit((BNotNode *)node);
        default:
            raise_error(node->line, "invalid node");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(IntNode *node)
    {
        return std::unique_ptr<Entity>(new Int(node->int_val));
    }

    std::unique_ptr<Entity> Interpreter::visit(DoubleNode *node)
    {
        return std::unique_ptr<Entity>(new Double(node->double_val));
    }

    std::unique_ptr<Entity> Interpreter::visit(StringNode *node)
    {
        return std::unique_ptr<Entity>(new Object(std::move(Builtins::class_string.get()->env), node->string_val));
    }

    std::unique_ptr<Entity> Interpreter::visit(TrueNode *node)
    {
        return std::unique_ptr<Entity>(new Bool(true));
    }

    std::unique_ptr<Entity> Interpreter::visit(FalseNode *node)
    {
        return std::unique_ptr<Entity>(new Bool(false));
    }

    std::unique_ptr<Entity> Interpreter::visit(NilNode *node)
    {
        return std::unique_ptr<Entity>(new Nil());
    }

    std::unique_ptr<Entity> Interpreter::visit(AddNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val + ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == INT_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val + ((Double *)b.get())->double_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val + ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val + ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '+'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(SubtractNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val - ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == INT_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val - ((Double *)b.get())->double_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val - ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val - ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '-'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(MultiplyNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val * ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == INT_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val * ((Double *)b.get())->double_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val * ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val * ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '*'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(DivideNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val / ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == INT_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Int *)a.get())->int_val / ((Double *)b.get())->double_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val / ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(((Double *)a.get())->double_val / ((Double *)b.get())->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '/'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(ModNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val % ((Int *)b.get())->int_val));
        }
        else if (a.get()->kind() == INT_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(std::fmod(((Int *)a.get())->int_val, ((Double *)b.get())->double_val)));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(std::fmod(((Double *)a.get())->double_val, ((Int *)b.get())->int_val)));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY && b.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(std::fmod(((Double *)a.get())->double_val, ((Double *)b.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '%'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(OrNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == BOOL_ENTITY && b.get()->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val || ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '||'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(AndNode *node)
    {
        // std::cout << "    std::unique_ptr<Entity> Interpreter::visit(AndNode *node)" << '\n';
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == BOOL_ENTITY && b.get()->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val && ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '&&'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(XorNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == BOOL_ENTITY && b.get()->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(((Bool *)a.get())->bool_val != ((Bool *)b.get())->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '^^'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BOrNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val | ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '|'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BAndNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val & ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '&'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BXorNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val ^ ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '^'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(LShiftNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val << ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '<<'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(RShiftNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node_a));
        std::unique_ptr<Entity> b = visit(std::move(node->node_b));

        if (a.get()->kind() == INT_ENTITY && b.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(((Int *)a.get())->int_val >> ((Int *)b.get())->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>>'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(PlusNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node));

        if (a.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(+(((Int *)a.get())->int_val)));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(+(((Double *)a.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(MinusNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node));

        if (a.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(-(((Int *)a.get())->int_val)));
        }
        else if (a.get()->kind() == DOUBLE_ENTITY)
        {
            return std::unique_ptr<Entity>(new Double(-(((Double *)a.get())->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(NotNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node));

        if (a.get()->kind() == BOOL_ENTITY)
        {
            return std::unique_ptr<Entity>(new Bool(!(((Bool *)a.get())->bool_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '!'");
        }
    }

    std::unique_ptr<Entity> Interpreter::visit(BNotNode *node)
    {
        std::unique_ptr<Entity> a = visit(std::move(node->node));

        if (a.get()->kind() == INT_ENTITY)
        {
            return std::unique_ptr<Entity>(new Int(~(((Int *)a.get())->int_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '~'");
        }
    }
}