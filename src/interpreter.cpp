#include <string>
#include <memory>
#include <vector>
#include <cmath>

#include "node.h"
#include "env.h"
#include "entity.h"
#include "object.h"
#include "builtins.h"
#include "arguments.h"
#include "interpreter.h"
#include "util.h"

namespace pluto
{
    Interpreter::Interpreter(std::string filename)
    {
        this->filename = filename;
        spotted_return_stmt = false;
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
        case CHAR_NODE:
            return visit((CharNode *)node, env);
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
        case ASSIGN_NODE:
            return visit((AssignNode *)node, env);
        case PLUS_NODE:
            return visit((PlusNode *)node, env);
        case MINUS_NODE:
            return visit((MinusNode *)node, env);
        case NOT_NODE:
            return visit((NotNode *)node, env);
        case BNOT_NODE:
            return visit((BNotNode *)node, env);
        case CALL_NODE:
            return visit((CallNode *)node, env);
        case MEMBER_ACCESS_NODE:
            return visit((MemberAccessNode *)node, env);
        case VAR_DEF_NODE:
            return visit((VarDefNode *)node, env);
        case CONST_DEF_NODE:
            return visit((ConstDefNode *)node, env);
        case BLOCK_NODE:
            return visit((BlockNode *)node, env);
        case IF_NODE:
            return visit((IfNode *)node, env);
        case IF_ELSE_NODE:
            return visit((IfElseNode *)node, env);
        case FOR_NODE:
            return visit((ForNode *)node, env);
        case WHILE_NODE:
            return visit((WhileNode *)node, env);
        case FUNC_DEF_NODE:
            return visit((FuncDefNode *)node, env);
        case RETURN_NODE:
            return visit((ReturnNode *)node, env);
        case LAMBDA_NODE:
            return visit((LambdaNode *)node, env);
        case CLASS_DEF_NODE:
            return visit((ClassDefNode *)node, env);
        case MODULE_DEF_NODE:
            return visit((ModuleDefNode *)node, env);
        default:
            raise_error(node->line, "invalid node");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(ProgramNode *node, std::shared_ptr<Env> env)
    {
        if (node->nodes.size() == 0)
        {
            return Nil::NIL;
        }

        for (int i = 0; i < node->nodes.size() - 1; i++)
        {
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

    std::shared_ptr<Entity> Interpreter::visit(CharNode *node, std::shared_ptr<Env> env)
    {
        return std::shared_ptr<Entity>(new Char(node->char_val));
    }

    std::shared_ptr<Entity> Interpreter::visit(StringNode *node, std::shared_ptr<Env> env)
    {
        return std::shared_ptr<Entity>(new Object(std::shared_ptr<Env>(new Env()), Builtins::class_string, node->string_val));
    }

    std::shared_ptr<Entity> Interpreter::visit(NameNode *node, std::shared_ptr<Env> env)
    {
        if (env->has(node->name))
        {
            return env->get(node->name);
        }
        else
        {
            raise_error(node->line, "cannot find symbol '" + node->name + "'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(TrueNode *node, std::shared_ptr<Env> env)
    {
        return Bool::TRUE;
    }

    std::shared_ptr<Entity> Interpreter::visit(FalseNode *node, std::shared_ptr<Env> env)
    {
        return Bool::FALSE;
    }

    std::shared_ptr<Entity> Interpreter::visit(NilNode *node, std::shared_ptr<Env> env)
    {
        return Nil::NIL;
    }

    std::shared_ptr<Entity> Interpreter::visit(AddNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind != INT_ENTITY && akind != DOUBLE_ENTITY)
        {
            raise_error(node->line, "invalid argument #1 to binary operator '+' (int or double expected, got " + error_desc(akind)+")");
        }

        if (bkind != INT_ENTITY && bkind != DOUBLE_ENTITY)
        {
            raise_error(node->line, "invalid argument #2 to binary operator '+' (int or double expected, got " + error_desc(bkind) + ")");
        }

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val + std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Int>(a)->int_val + std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val + std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val + std::static_pointer_cast<Double>(b)->double_val));
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(SubtractNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val - std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Int>(a)->int_val - std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val - std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val - std::static_pointer_cast<Double>(b)->double_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val * std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Int>(a)->int_val * std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val * std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val * std::static_pointer_cast<Double>(b)->double_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val / std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Int>(a)->int_val / std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val / std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::static_pointer_cast<Double>(a)->double_val / std::static_pointer_cast<Double>(b)->double_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val % std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::fmod(std::static_pointer_cast<Int>(a)->int_val, std::static_pointer_cast<Double>(b)->double_val)));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::fmod(std::static_pointer_cast<Double>(a)->double_val, std::static_pointer_cast<Int>(b)->int_val)));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(std::fmod(std::static_pointer_cast<Double>(a)->double_val, std::static_pointer_cast<Double>(b)->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '%'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(AndNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == BOOL_ENTITY && bkind == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Bool>(a)->bool_val && std::static_pointer_cast<Bool>(b)->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '&&'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(OrNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == BOOL_ENTITY && bkind == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Bool>(a)->bool_val || std::static_pointer_cast<Bool>(b)->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '||'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(XorNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == BOOL_ENTITY && bkind == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Bool>(a)->bool_val != std::static_pointer_cast<Bool>(b)->bool_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '^^'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(BAndNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val & std::static_pointer_cast<Char>(b)->char_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val ^ std::static_pointer_cast<Int>(b)->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '|'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(BOrNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val | std::static_pointer_cast<Int>(b)->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '|'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(EENode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val == std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val == std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == CHAR_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val == std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == BOOL_ENTITY && bkind == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Bool>(a)->bool_val == std::static_pointer_cast<Bool>(b)->bool_val));
        }
        else if (akind == OBJECT_ENTITY && bkind == OBJECT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(a.get() == b.get()));
        }
        else
        {
            return Bool::FALSE;
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(NENode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val != std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val != std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == CHAR_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val != std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == BOOL_ENTITY && bkind == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Bool>(a)->bool_val != std::static_pointer_cast<Bool>(b)->bool_val));
        }
        else if (akind == OBJECT_ENTITY && bkind == OBJECT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(a.get() != b.get()));
        }
        else
        {
            return Bool::TRUE;
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(LTNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == CHAR_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val < std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == CHAR_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val < std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == CHAR_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val < std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == INT_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val < std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val < std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val < std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val < std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val < std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val < std::static_pointer_cast<Double>(b)->double_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == CHAR_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val > std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == CHAR_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val > std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == CHAR_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val > std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == INT_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val > std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val > std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val > std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val > std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val > std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val > std::static_pointer_cast<Double>(b)->double_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == CHAR_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val <= std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == CHAR_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val <= std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == CHAR_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val <= std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == INT_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val <= std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val <= std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val <= std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val <= std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val <= std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val <= std::static_pointer_cast<Double>(b)->double_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == CHAR_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val >= std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == CHAR_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val >= std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == CHAR_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Char>(a)->char_val >= std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == INT_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val >= std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val >= std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == INT_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Int>(a)->int_val >= std::static_pointer_cast<Double>(b)->double_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val >= std::static_pointer_cast<Char>(b)->char_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val >= std::static_pointer_cast<Int>(b)->int_val));
        }
        else if (akind == DOUBLE_ENTITY && bkind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(std::static_pointer_cast<Double>(a)->double_val >= std::static_pointer_cast<Double>(b)->double_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>='");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(LShiftNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node_a, env);
        std::shared_ptr<Entity> b = visit(node->node_b, env);

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val << std::static_pointer_cast<Int>(b)->int_val));
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

        EntityKind akind = a->kind();
        EntityKind bkind = b->kind();

        if (akind == INT_ENTITY && bkind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Int>(a)->int_val >> std::static_pointer_cast<Int>(b)->int_val));
        }
        else
        {
            raise_error(node->line, "invalid operands for binary operator '>>'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(AssignNode *node, std::shared_ptr<Env> env)
    {
        if (node->key->kind() == MEMBER_ACCESS_NODE)
        {
            MemberAccessNode *key_node = std::static_pointer_cast<MemberAccessNode>(node->key).get();

            std::shared_ptr<Entity> subject = visit(key_node->subject, env);

            if (subject->kind() != OBJECT_ENTITY)
            {
                raise_error(node->line, "cannot access a member of " + error_desc(subject->kind(), true) + "valu");
            }

            std::string member = key_node->member;

            std::shared_ptr<Env> subject_env = std::static_pointer_cast<Object>(subject)->env;

            std::shared_ptr<Entity> val = visit(node->val, env);

            subject_env->set(member, val);

            return Nil::NIL;
        }

        if (node->key->kind() != NAME_NODE)
        {
            raise_error(node->line, "invalid left-hand side in assignment");
        }

        std::string key = std::static_pointer_cast<NameNode>(node->key)->name;

        if (!env->has(key))
        {
            raise_error(node->line, "cannot find symbol '" + key + "'");
        }

        std::shared_ptr<Entity> val = visit(node->val, env);

        (env->resolve(key))->set(key, val);

        return val;
    }

    std::shared_ptr<Entity> Interpreter::visit(PlusNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        EntityKind akind = a->kind();

        if (akind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(+(std::static_pointer_cast<Int>(a)->int_val)));
        }
        else if (akind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(+(std::static_pointer_cast<Double>(a)->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(MinusNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        EntityKind akind = a->kind();

        if (akind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(-(std::static_pointer_cast<Int>(a)->int_val)));
        }
        else if (akind == DOUBLE_ENTITY)
        {
            return std::shared_ptr<Entity>(new Double(-(std::static_pointer_cast<Double>(a)->double_val)));
        }
        else
        {
            raise_error(node->line, "invalid operands for unary operator '-'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(NotNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        EntityKind akind = a->kind();

        if (akind == BOOL_ENTITY)
        {
            return std::shared_ptr<Entity>(new Bool(!(std::static_pointer_cast<Bool>(a)->bool_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '!'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(BNotNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> a = visit(node->node, env);

        EntityKind akind = a->kind();

        if (akind == CHAR_ENTITY)
        {
            return std::shared_ptr<Entity>(new Char(~(std::static_pointer_cast<Char>(a)->char_val)));
        }
        else if (akind == INT_ENTITY)
        {
            return std::shared_ptr<Entity>(new Int(~(std::static_pointer_cast<Int>(a)->int_val)));
        }
        else
        {
            raise_error(node->line, "invalid operand for unary operator '~'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(CallNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> self;

        if (node->callee->kind() == MEMBER_ACCESS_NODE)
        {
            self = visit(std::static_pointer_cast<MemberAccessNode>(node->callee)->subject, env);
        }

        std::shared_ptr<Entity> callee = visit(node->callee, env);

        std::vector<std::shared_ptr<Entity> > data;

        for (int i = 0; i < node->args.size(); i++)
        {
            data.push_back(visit(node->args[i], env));
        }

        std::shared_ptr<Arguments> args(new Arguments(filename, node->line, data));

        args->self = self;

        if (std::static_pointer_cast<Object>((callee))->func)
        {
            return std::static_pointer_cast<Object>(callee)->func(args);
        }

        if (callee->kind() != OBJECT_ENTITY)
        {
            raise_error(node->line, callee->str() + " is not callable");
        }

        std::shared_ptr<Env> class_env = std::static_pointer_cast<Object>((callee))->env;

        std::shared_ptr<Entity> obj(new Object(class_env));

        if (class_env->has("constructor"))
        {
            std::shared_ptr<Entity> constructor = class_env->get("constructor");

            if (constructor->kind() == OBJECT_ENTITY && (std::static_pointer_cast<Object>((constructor))->func))
            {
                std::shared_ptr<Arguments> args(new Arguments(filename, node->line, data));

                args->self = obj;

                std::static_pointer_cast<Object>(constructor)->func(args);
            }
        }

        return obj;
    }

    std::shared_ptr<Entity> Interpreter::visit(MemberAccessNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> subject = visit(node->subject, env);
        EntityKind subjectkind = subject->kind();

        if (subjectkind != OBJECT_ENTITY)
        {
            raise_error(node->line, "cannot access a member of " + error_desc(subjectkind, true) + " value");
        }

        std::string member = node->member;

        Object *sub = std::static_pointer_cast<Object>(subject).get();

        std::shared_ptr<Env> subject_env = sub->env;

        if (subject_env->has(member))
        {
            return subject_env->get(member);
        }
        else
        {
            if (sub->type->kind() == OBJECT_ENTITY)
            {
                std::shared_ptr<Env> subject_type_env = std::static_pointer_cast<Object>(sub->type)->env;
                if (subject_type_env->has(member))
                {
                    return subject_type_env->get(member);
                }
            }

            raise_error(node->line, "cannot find member '" + member + "'");
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(VarDefNode *node, std::shared_ptr<Env> env)
    {
        if (env->map.count(node->key) == 1)
        {
            raise_error(node->line, "name '" + node->key + "' is already defined");
        }

        std::shared_ptr<Entity> val = visit(node->val, env);

        env->set(node->key, val);

        return val;
    }

    std::shared_ptr<Entity> Interpreter::visit(ConstDefNode *node, std::shared_ptr<Env> env)
    {
        if (env->map.count(node->key) == 1)
        {
            raise_error(node->line, "name '" + node->key + "' is already defined");
        }

        std::shared_ptr<Entity> val = visit(node->val, env);

        env->set(node->key, val, true);

        return val;
    }

    std::shared_ptr<Entity> Interpreter::visit(BlockNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Env> child_env(new Env(env));

        return visit(node->node, child_env);
    }

    std::shared_ptr<Entity> Interpreter::visit(IfNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> cond = visit(node->cond, env);

        if (cond->is_true())
        {
            return visit(node->body, env);
        }
        else
        {
            return Nil::NIL;
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(IfElseNode *node, std::shared_ptr<Env> env)
    {
        std::shared_ptr<Entity> cond = visit(node->cond, env);

        if (cond->is_true())
        {
            return visit(node->body, env);
        }
        else
        {
            return visit(node->else_body, env);
        }
    }

    std::shared_ptr<Entity> Interpreter::visit(ForNode *node, std::shared_ptr<Env> env)
    {
        visit(node->stmt_a, env);

        while (true)
        {
            std::shared_ptr<Entity> cond = visit(node->stmt_b, env);

            if (!cond->is_true())
            {
                break;
            }

            visit(node->stmt_c, env);

            visit(node->body, env);
        }

        return Nil::NIL;
    }

    std::shared_ptr<Entity> Interpreter::visit(WhileNode *node, std::shared_ptr<Env> env)
    {
        while (true)
        {
            std::shared_ptr<Entity> cond = visit(node->cond, env);

            if (!cond->is_true())
            {
                break;
            }

            visit(node->body, env);
        }

        return Nil::NIL;
    }

    std::shared_ptr<Entity> Interpreter::visit(FuncDefNode *node, std::shared_ptr<Env> env)
    {
        if (env->map.count(node->name) == 1)
        {
            raise_error(node->line, "name '" + node->name + "' is already defined");
        }

        func_t new_func = [this, node, env](std::shared_ptr<Arguments> args)
        {
            std::shared_ptr<Env> child_env(new Env(env));

            for (int i = 0; i < node->args.size(); i++)
            {
                child_env->set(node->args.at(i), args->at(i));
            }

            if (args->self != nullptr)
            {
                child_env->set("self", args->self);
            }

            BlockNode *block_node = (BlockNode *)node;
            std::vector<std::shared_ptr<Node> > nodes = std::static_pointer_cast<ProgramNode>(block_node->node)->nodes;

            for (int i = 0; i < nodes.size(); i++)
            {
                std::shared_ptr<Entity> val = visit(nodes.at(i), child_env);
                if (spotted_return_stmt)
                {
                    return val;
                }
            }

            return Nil::NIL;
        };

        std::shared_ptr<Entity> obj(new Object(std::shared_ptr<Env>(new Env()), Builtins::class_func, new_func));

        env->set(node->name, obj);

        return Nil::NIL;
    }

    std::shared_ptr<Entity> Interpreter::visit(ReturnNode *node, std::shared_ptr<Env> env)
    {
        spotted_return_stmt = true;
        return visit(node->node, env);
    }

    std::shared_ptr<Entity> Interpreter::visit(LambdaNode *node, std::shared_ptr<Env> env)
    {
        func_t new_func = [this, node, env](std::shared_ptr<Arguments> args)
        {
            std::shared_ptr<Env> child_env(new Env(env));

            for (int i = 0; i < node->args.size(); i++)
            {
                child_env->set(node->args.at(i), args->at(i));
            }

            if (node->body->kind() != BLOCK_NODE)
            {
                return visit(node->body, child_env);
            }

            BlockNode *block_node = (BlockNode *)node;
            std::vector<std::shared_ptr<Node> > nodes = std::static_pointer_cast<ProgramNode>(block_node->node)->nodes;

            for (int i = 0; i < nodes.size(); i++)
            {
                std::shared_ptr<Entity> val = visit(nodes.at(i), child_env);
                if (spotted_return_stmt)
                {
                    return val;
                }
            }

            return Nil::NIL;
        };

        return std::shared_ptr<Entity>(new Object(std::shared_ptr<Env>(new Env()), Builtins::class_func, new_func));
    }

    std::shared_ptr<Entity> Interpreter::visit(ClassDefNode *node, std::shared_ptr<Env> env)
    {
        if (env->map.count(node->name) == 1)
        {
            raise_error(node->line, "name '" + node->name + "' is already defined");
        }

        std::shared_ptr<Env> child_env(new Env(env));

        std::shared_ptr<Node> body = ((std::static_pointer_cast<BlockNode>(node->body)->node));

        visit(body, child_env);

        Object *c1 = new Object(Builtins::class_env, Builtins::class_object);
        c1->env->map = child_env->map;

        std::shared_ptr<Entity> c2(c1);

        env->set(node->name, c2);

        return Nil::NIL;
    }

    std::shared_ptr<Entity> Interpreter::visit(ModuleDefNode *node, std::shared_ptr<Env> env)
    {
        if (env->map.count(node->name) == 1)
        {
            std::shared_ptr<Entity> mod = env->get(node->name);

            if (mod->kind() != OBJECT_ENTITY)
            {
                raise_error(node->line, "name '" + node->name + "' is already defined");
            }

            visit(std::static_pointer_cast<BlockNode>((node->body))->node, std::static_pointer_cast<Object>((mod))->env);
        }
        else
        {
            std::shared_ptr<Env> child_env(new Env(env));

            visit(std::static_pointer_cast<BlockNode>((node->body))->node, child_env);

            std::shared_ptr<Env> module_env(new Env(Builtins::module_env));
            module_env->map = child_env->map;

            env->set(node->name, std::shared_ptr<Entity>(new Object(module_env)));
        }

        return Nil::NIL;
    }
}