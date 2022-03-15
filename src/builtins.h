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
        static const std::shared_ptr<Entity> func_print;
        static const std::shared_ptr<Env> func_env;
    };
}

#endif