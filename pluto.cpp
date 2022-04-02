#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <string>
#include <memory>
#include <vector>

#include "src/token.cpp"
#include "src/lexer.cpp"
#include "src/node.cpp"
#include "src/parser.cpp"
#include "src/object.cpp"
#include "src/env.cpp"
#include "src/entity.cpp"
#include "src/builtins.cpp"
#include "src/arguments.cpp"
#include "src/interpreter.cpp"

void run(std::string filename, std::string text)
{
    pluto::Lexer lexer(filename, text);
    std::vector<pluto::Token> tokens = lexer.generate_tokens();
    
    pluto::Parser parser(filename, tokens);
    std::shared_ptr<pluto::Node> tree = parser.parse();

    std::shared_ptr<pluto::Env> global_env(new pluto::Env());

    global_env->set("Class", pluto::Builtins::class_class);
    global_env->set("Object", pluto::Builtins::class_object);
    global_env->set("String", pluto::Builtins::class_string);
    global_env->set("List", pluto::Builtins::class_list);
    global_env->set("Func", pluto::Builtins::class_func);
    global_env->set("Module", pluto::Builtins::class_module);    
    global_env->set("Math", pluto::Builtins::class_math);
    global_env->set("print", pluto::Builtins::func_print);
    global_env->set("println", pluto::Builtins::func_println);

    pluto::Builtins::object_env->set("toString", pluto::Builtins::func_object_tostring);

    pluto::Builtins::string_env->set("charAt", pluto::Builtins::func_string_charat);
    pluto::Builtins::string_env->set("first", pluto::Builtins::func_string_first);
    pluto::Builtins::string_env->set("last", pluto::Builtins::func_string_last);
    pluto::Builtins::string_env->set("length", pluto::Builtins::func_string_length);
    pluto::Builtins::string_env->set("toString", pluto::Builtins::func_string_tostring);

    pluto::Builtins::list_env->set("get", pluto::Builtins::func_list_get);
    pluto::Builtins::list_env->set("set", pluto::Builtins::func_list_set);
    pluto::Builtins::list_env->set("size", pluto::Builtins::func_list_size);
    pluto::Builtins::list_env->set("toString", pluto::Builtins::func_list_tostring);

    pluto::Builtins::math_env->set("acos", pluto::Builtins::func_math_acos);
    pluto::Builtins::math_env->set("asin", pluto::Builtins::func_math_asin);
    pluto::Builtins::math_env->set("atan", pluto::Builtins::func_math_asin);
    pluto::Builtins::math_env->set("sqrt", pluto::Builtins::func_math_sqrt);

    pluto::Interpreter interpreter(filename);
    interpreter.visit(std::move(tree), std::move(global_env));
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