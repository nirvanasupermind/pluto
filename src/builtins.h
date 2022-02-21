#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>
#include <memory>

#include "env.h"
#include "entity.h"
#include "concept.h"

namespace pluto
{
    class Builtins
    {
    public:
        static const std::unique_ptr<Class> class_object;
        static const std::unique_ptr<Class> class_string;
    };
}

#endif