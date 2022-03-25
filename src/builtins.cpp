#include <string>
#include <memory>
#include <iostream>

#include "env.h"
#include "entity.h"
#include "object.h"
#include "builtins.h"
#include "arguments.h"

namespace pluto
{
    const std::shared_ptr<Entity> Builtins::class_class(new Object());
    const std::shared_ptr<Env> Builtins::class_env = ((Object *)(Builtins::class_class.get()))->env;
    const std::shared_ptr<Entity> Builtins::class_object(new Object(std::shared_ptr<Env>(new Env(Builtins::class_env))));
    const std::shared_ptr<Entity> Builtins::class_string(new Object(std::shared_ptr<Env>(new Env(Builtins::class_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_array(new Object(std::shared_ptr<Env>(new Env(Builtins::class_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_func(new Object(std::shared_ptr<Env>(new Env(Builtins::class_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_module(new Object(std::shared_ptr<Env>(new Env(Builtins::class_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_math(new Object(std::shared_ptr<Env>(new Env(Builtins::class_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_system(new Object(std::shared_ptr<Env>(new Env(Builtins::class_env)), Builtins::class_object));

    const std::shared_ptr<Env> Builtins::object_env = ((Object *)(Builtins::class_object.get()))->env;
    const std::shared_ptr<Env> Builtins::string_env = ((Object *)(Builtins::class_string.get()))->env;
    const std::shared_ptr<Env> Builtins::array_env = ((Object *)(Builtins::class_array.get()))->env;
    const std::shared_ptr<Env> Builtins::func_env = ((Object *)(Builtins::class_func.get()))->env;
    const std::shared_ptr<Env> Builtins::module_env = ((Object *)(Builtins::class_module.get()))->env;
    const std::shared_ptr<Env> Builtins::math_env = ((Object *)(Builtins::class_math.get()))->env;
    const std::shared_ptr<Env> Builtins::system_env = ((Object *)(Builtins::class_system.get()))->env;

    const std::shared_ptr<Entity> Builtins::func_string_tostring(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args)
                                                                            { return args->self; }));

    const std::shared_ptr<Entity> Builtins::func_math_acos(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args)
                                                                      {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        if(akind == CHAR) {
            return std::shared_ptr<Entity>(new Double(std::acos(((Char *)a.get())->char_val)));
        } else if(akind == INT) {
            return std::shared_ptr<Entity>(new Double(std::acos(((Int *)a.get())->int_val)));
        } else if(akind == DOUBLE) {
            return std::shared_ptr<Entity>(new Double(std::acos(((Double *)a.get())->double_val)));
        } else {
             throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'acos' (double expected, got " + error_desc(akind) + ")");
        } }));

    const std::shared_ptr<Entity> Builtins::func_math_asin(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args)
                                                                      {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        if(akind == CHAR) {
            return std::shared_ptr<Entity>(new Double(std::asin(((Char *)a.get())->char_val)));
        } else if(akind == INT) {
            return std::shared_ptr<Entity>(new Double(std::asin(((Int *)a.get())->int_val)));
        } else if(akind == DOUBLE) {
            return std::shared_ptr<Entity>(new Double(std::asin(((Double *)a.get())->double_val)));
        } else {
            throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'asin' (double expected, got " + error_desc(akind) + ")");
        } }));

    const std::shared_ptr<Entity> Builtins::func_math_atan(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args)
                                                                      {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        if(akind == CHAR) {
            return std::shared_ptr<Entity>(new Double(std::atan(((Char *)a.get())->char_val)));
        } else if(akind == INT) {
            return std::shared_ptr<Entity>(new Double(std::atan(((Int *)a.get())->int_val)));
        } else if(akind == DOUBLE) {
            return std::shared_ptr<Entity>(new Double(std::atan(((Double *)a.get())->double_val)));
        } else {
            throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'atan' (double expected, got " + error_desc(akind) + ")");
        } }));

    const std::shared_ptr<Entity> Builtins::func_string_charat(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args)
                                                                          {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        std::string string_val = ((Object *)args->self.get())->string_val;
        int string_len = string_val.length();

        if(akind == INT) {
            int int_val = ((Int *)a.get())->int_val;

            if(int_val >= string_len || int_val < 0) {
                throw std::string(args->filename + ":" + std::to_string(args->line) + ": string index out of range");
            }

            return std::shared_ptr<Entity>((new Char(string_val[int_val])));
        } else {
             throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'charAt' (int expected, got " + error_desc(akind) + ")");
        } }));

    const std::shared_ptr<Entity> Builtins::func_system_print(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args)
                                                                         {
        std::shared_ptr<Entity> arg = args->at(0);

        std::string s = arg->to_string();
        
        if (arg->kind() == OBJECT_ENTITY)
        {
            std::shared_ptr<Env> env = ((Object *)(arg.get()))->env;

            if (env->has("toString"))
            {
                func_t func = ((Object *)((env->get("toString")).get()))->func;

                if (func)
                {                        
                    std::shared_ptr<Arguments> args2(new Arguments(args->filename, args->line, std::vector<std::shared_ptr<Entity> >()));
                    args2->self = arg;

                    std::shared_ptr<Entity> res = func(args2);

                    if (res->kind() == OBJECT_ENTITY)
                    {
                        s = ((Object *)res.get())->string_val;
                    }
                }
            }
        }

        std::cout << s << '\n';

        return Nil::NIL; }));
}