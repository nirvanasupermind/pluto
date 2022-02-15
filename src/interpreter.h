#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <memory>

#include "node.h"
#include "env.h"
#include "entity.h"
#include "object.h"
#include "builtins.h"

namespace pluto
{
    class Interpreter
    {
    public:
        std::string filename;
        
        Interpreter(std::string filename);

        void raise_error(int line, std::string message);
        
        std::unique_ptr<Entity> visit(std::unique_ptr<Node> node);
        std::unique_ptr<Entity> visit(Node *node);
        std::unique_ptr<Entity> visit(IntNode *node);
        std::unique_ptr<Entity> visit(DoubleNode *node);
        std::unique_ptr<Entity> visit(StringNode *node);
        std::unique_ptr<Entity> visit(AddNode *node);
        std::unique_ptr<Entity> visit(SubtractNode *node);
        std::unique_ptr<Entity> visit(MultiplyNode *node);
        std::unique_ptr<Entity> visit(DivideNode *node);
        std::unique_ptr<Entity> visit(ModNode *node);
        std::unique_ptr<Entity> visit(PlusNode *node);
        std::unique_ptr<Entity> visit(MinusNode *node);
    };
}

#endif