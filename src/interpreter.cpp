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
    Interpreter::Interpreter(std::string filename) {
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
        case STRING_NODE:
            return visit((StringNode *)node);
        default: {
            raise_error(node->line, "invalid node");
        }
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