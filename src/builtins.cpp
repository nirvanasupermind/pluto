#include <string>
#include <memory>

#include "env.h"
#include "entity.h"
#include "concept.h"
#include "builtins.h"

namespace pluto
{
    std::shared_ptr<Entity> Builtins::class_object(new Class());
    std::shared_ptr<Entity> Builtins::class_string(new Class(((Class *)(Builtins::class_object.get()))->env));
}