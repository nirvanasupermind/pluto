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
    std::unique_ptr<pluto::Node> tree = parser.parse();

    std::unique_ptr<pluto::Env> global_env = std::unique_ptr<pluto::Env>(new pluto::Env());
    global_env->set("Object", std::move(pluto::Builtins::class_object));
    global_env->set("String", std::move(pluto::Builtins::class_string));

    pluto::Interpreter interpreter(filename);
    // final result is stored in entity
    std::unique_ptr<pluto::Entity> entity = interpreter.visit(std::move(tree), std::move(global_env));
    
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
        
        std::unique_ptr<Entity> visit(std::unique_ptr<Node> node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(Node *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(EmptyNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(IntNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(DoubleNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(StringNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(NameNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(TrueNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(FalseNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(NilNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(AddNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(SubtractNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(MultiplyNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(DivideNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(OrNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(AndNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(XorNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(BOrNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(BAndNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(BXorNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(LShiftNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(RShiftNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(EENode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(NENode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(LTNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(GTNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(LTENode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(GTENode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(ModNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(PlusNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(MinusNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(NotNode *node, std::unique_ptr<Env> env);
        std::unique_ptr<Entity> visit(BNotNode *node, std::unique_ptr<Env> env);
    };
}

#endif