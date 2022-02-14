#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>
#include <memory>

#include "env.h"
#include "entity.h"
#include "object.h"

namespace pluto
{
    class Builtins
    {
    public:
        static const std::unique_ptr<Object> class_object;
        static const std::unique_ptr<Object> class_string;
    };
}

#endif