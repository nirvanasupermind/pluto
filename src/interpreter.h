#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <memory>

#include "node.h"
#include "env.h"
#include "entity.h"
#include "concept.h"
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
        std::unique_ptr<Entity> visit(TrueNode *node);
        std::unique_ptr<Entity> visit(FalseNode *node);
        std::unique_ptr<Entity> visit(NilNode *node);
        std::unique_ptr<Entity> visit(AddNode *node);
        std::unique_ptr<Entity> visit(SubtractNode *node);
        std::unique_ptr<Entity> visit(MultiplyNode *node);
        std::unique_ptr<Entity> visit(DivideNode *node);
        std::unique_ptr<Entity> visit(OrNode *node);
        std::unique_ptr<Entity> visit(AndNode *node);
        std::unique_ptr<Entity> visit(XorNode *node);
        std::unique_ptr<Entity> visit(BOrNode *node);
        std::unique_ptr<Entity> visit(BAndNode *node);
        std::unique_ptr<Entity> visit(BXorNode *node);
        std::unique_ptr<Entity> visit(ModNode *node);
        std::unique_ptr<Entity> visit(PlusNode *node);
        std::unique_ptr<Entity> visit(MinusNode *node);
        std::unique_ptr<Entity> visit(NotNode *node);
        std::unique_ptr<Entity> visit(BNotNode *node);
    };
}

#endif