#include <string>
#include <memory>
#include <iostream>

#include "env.h"
#include "entity.h"
#include "concept.h"
#include "builtins.h"
#include "arguments.h"

namespace pluto
{
    const std::shared_ptr<Entity> Builtins::class_type(new Object());
    const std::shared_ptr<Env> Builtins::type_env = ((Object *)(Builtins::class_type.get()))->env;
    const std::shared_ptr<Entity> Builtins::class_object(new Object(std::shared_ptr<Env>(new Env(Builtins::type_env))));
    const std::shared_ptr<Entity> Builtins::class_string(new Object(std::shared_ptr<Env>(new Env(Builtins::type_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_func(new Object(std::shared_ptr<Env>(new Env(Builtins::type_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_module(new Object(std::shared_ptr<Env>(new Env(Builtins::type_env)), Builtins::class_object));
    const std::shared_ptr<Entity> Builtins::class_system(new Object(std::shared_ptr<Env>(new Env(Builtins::type_env)),Builtins::class_object));
    
    const std::shared_ptr<Env> Builtins::object_env = ((Object *)(Builtins::class_object.get()))->env;
    const std::shared_ptr<Env> Builtins::string_env = ((Object *)(Builtins::class_string.get()))->env;
    const std::shared_ptr<Env> Builtins::func_env = ((Object *)(Builtins::class_func.get()))->env;
    const std::shared_ptr<Env> Builtins::module_env = ((Object *)(Builtins::class_module.get()))->env;
    const std::shared_ptr<Env> Builtins::system_env = ((Object *)(Builtins::class_system.get()))->env;

    const std::shared_ptr<Entity> Builtins::func_string_tostring(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args) {
        return args->self;
    }));

    const std::shared_ptr<Entity> Builtins::func_system_print(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args) {
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

        return Nil::NIL;
    }));
}