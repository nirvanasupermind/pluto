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
    const std::shared_ptr<Env> Builtins::func_env = ((Class *)(Builtins::class_func.get()))->env;
    const std::shared_ptr<Entity> Builtins::func_print(new Object(Builtins::func_env, [](std::shared_ptr<Arguments> args) {
        for(int i = 0; i < args->data.size(); i++) {
            std::cout << args->at(i)->to_string() << " ";
        }
        
        std::cout << '\n';

        return Nil::NIL;
    }));
}