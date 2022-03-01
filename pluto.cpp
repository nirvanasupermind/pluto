#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <vector>
#include <string>

#include "src/token.cpp"
#include "src/lexer.cpp"
#include "src/node.cpp"
#include "src/parser.cpp"
#include "src/env.cpp"
#include "src/entity.cpp"
#include "src/concept.cpp"
#include "src/builtins.cpp"
#include "src/interpreter.cpp"

void run(std::string filename, std::string text)
{
    pluto::Lexer lexer(filename, text);
    std::vector<pluto::Token> tokens = lexer.generate_tokens();
    
    pluto::Parser parser(filename, tokens);
    std::shared_ptr<pluto::Node> tree = parser.parse();

    std::shared_ptr<pluto::Env> global_env = std::shared_ptr<pluto::Env>(new pluto::Env());
    global_env->set("Object", std::move(pluto::Builtins::class_object));
    global_env->set("String", std::move(pluto::Builtins::class_string));

    pluto::Interpreter interpreter(filename);
    // final result is stored in entity
    std::shared_ptr<pluto::Entity> entity = interpreter.visit(std::move(tree), std::move(global_env));
    
    std::cout << entity->to_string() << '\n';
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: pluto [script]" << '\n';
    }
    else
    {
        std::string filename(argv[1]);
        std::ifstream inFile;

        inFile.open(filename);

        std::stringstream strStream;
        strStream << inFile.rdbuf();

        std::string text = strStream.str();
        
        try
        {
            run(filename, text);
        }
        catch (std::string e)
        {   
            std::cerr << e << '\n';
        }
    }
}



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
        
        std::shared_ptr<Entity> visit(std::shared_ptr<Node> node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(Node *node, std::shared_ptr<Env> env);
        std::shared_ptr<Entity> visit(EmptyNode *node, std::shared_ptr<Env> env);
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