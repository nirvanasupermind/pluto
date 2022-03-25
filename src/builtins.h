#ifndef BUILTINS_H
#define BUILTINS_H

#include <iostream>
#include <string>
#include <memory>
#include <cmath>

#include "env.h"
#include "entity.h"
#include "object.h"
#include "arguments.h"

namespace pluto
{
    class Builtins
    {
    public:
        static const std::shared_ptr<Entity> class_class;
        static const std::shared_ptr<Entity> class_object;
        static const std::shared_ptr<Entity> class_string;
        static const std::shared_ptr<Entity> class_array;
        static const std::shared_ptr<Entity> class_func;
        static const std::shared_ptr<Entity> class_module;
        static const std::shared_ptr<Entity> class_math;
        static const std::shared_ptr<Entity> class_system;
        static const std::shared_ptr<Env> class_env;
        static const std::shared_ptr<Env> object_env;
        static const std::shared_ptr<Env> string_env;
        static const std::shared_ptr<Env> array_env;
        static const std::shared_ptr<Env> func_env;
        static const std::shared_ptr<Env> math_env;
        static const std::shared_ptr<Env> module_env;
        static const std::shared_ptr<Env> system_env;
        static const std::shared_ptr<Entity> func_string_charat;
        static const std::shared_ptr<Entity> func_string_tostring;
        static const std::shared_ptr<Entity> func_math_acos;
        static const std::shared_ptr<Entity> func_math_asin;
        static const std::shared_ptr<Entity> func_math_atan;
        static const std::shared_ptr<Entity> func_math_cos;
        static const std::shared_ptr<Entity> func_math_sin;
        static const std::shared_ptr<Entity> func_math_tan;
        static const std::shared_ptr<Entity> func_system_print;
    };
}

#endif