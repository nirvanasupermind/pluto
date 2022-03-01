#ifndef INTERPRETER_H
#define INTERPRETER_H

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
        
        std::shared_ptr<Entity> visit(std::shared_ptr<Node> node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(Node *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(ProgramNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(IntNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(DoubleNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(StringNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(NameNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(TrueNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(FalseNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(NilNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(AddNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(SubtractNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(MultiplyNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(DivideNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(OrNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(AndNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(XorNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(BOrNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(BAndNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(BXorNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(LShiftNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(RShiftNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(EENode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(NENode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(LTNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(GTNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(LTENode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(GTENode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(ModNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(PlusNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(MinusNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(NotNode *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(BNotNode *node, std::shared_ptr<Env> env);
    };
}

#endif