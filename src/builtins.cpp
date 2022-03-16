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
    const std::shared_ptr<Entity> Builtins::class_object(new Class());
    const std::shared_ptr<Entity> Builtins::class_string(new Class(((Class *)(Builtins::class_object.get()))->env));
    const std::shared_ptr<Entity> Builtins::class_func(new Class(((Class *)(Builtins::class_object.get()))->env));
    const std::shared_ptr<Entity> Builtins::class_stdout(new Class(((Class *)(Builtins::class_object.get()))->env));

    const std::shared_ptr<Env> Builtins::string_env = ((Class *)(Builtins::class_string.get()))->env;
    const std::shared_ptr<Env> Builtins::func_env = ((Class *)(Builtins::class_func.get()))->env;
    const std::shared_ptr<Env> Builtins::stdout_env = ((Class *)(Builtins::class_stdout.get()))->env;

    const std::shared_ptr<Entity> Builtins::func_string_tostring(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args) {
        return args->self;
    }));

    const std::shared_ptr<Entity> Builtins::func_stdout_flush(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args) {
        std::cout << std::flush;
        return Nil::NIL;
    }));

    const std::shared_ptr<Entity> Builtins::func_stdout_write(new Object(std::shared_ptr<Env>(new Env(Builtins::func_env)), [](std::shared_ptr<Arguments> args) {
        for (int i = 0; i < args->data.size(); i++)
        {
            std::shared_ptr<Entity> arg = args->at(i);

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

            std::cout << s;
        }

        return Nil::NIL;
    }));
}