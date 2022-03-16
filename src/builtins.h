#ifndef BUILTINS_H
#define BUILTINS_H

#include <iostream>
#include <string>
#include <memory>

#include "env.h"
#include "entity.h"
#include "concept.h"
#include "arguments.h"

namespace pluto
{
    class Builtins
    {
    public:
        static const std::shared_ptr<Entity> class_object;
        static const std::shared_ptr<Entity> class_string;
        static const std::shared_ptr<Entity> class_func;
        static const std::shared_ptr<Entity> class_stdout;
        static const std::shared_ptr<Env> object_env;
        static const std::shared_ptr<Env> string_env;
        static const std::shared_ptr<Env> func_env;
        static const std::shared_ptr<Env> stdout_env;
        static const std::shared_ptr<Entity> func_string_tostring;
        static const std::shared_ptr<Entity> func_stdout_flush;
        static const std::shared_ptr<Entity> func_stdout_write;
    };
}

#endif