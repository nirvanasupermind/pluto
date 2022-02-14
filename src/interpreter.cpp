#include <string>
#include <memory>

#include "node.h"
#include "env.h"
#include "entity.h"
#include "object.h"
#include "builtins.h"
#include "interpreter.h"

namespace pluto
{
    std::unique_ptr<Entity> Interpreter::visit(std::unique_ptr<Node> node)
    {
        return visit(node.get());
    }

    std::unique_ptr<Entity> Interpreter::visit(Node *node)
    {
        switch (node->kind())
        {
        case INT_NODE:
            return visit((IntNode *)node);
        case DOUBLE_NODE:
            return visit((DoubleNode *)node);
        case STRING_NODE:
            return visit((StringNode *)node);
        default:
            throw "invalid node";
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
}