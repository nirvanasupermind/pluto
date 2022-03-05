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
        static const std::shared_ptr<Entity> class_object;
        static const std::shared_ptr<Entity> class_string;
    };
}

#endif