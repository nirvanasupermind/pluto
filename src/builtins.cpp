#include <string>
#include <memory>
#include <iostream>

#include "env.h"
#include "entity.h"
#include "concept.h"
#include "builtins.h"

namespace pluto
{
    const std::shared_ptr<Entity> Builtins::class_object(new Class());
    const std::shared_ptr<Entity> Builtins::class_string(new Class(((Class *)(Builtins::class_object.get()))->env));
    const std::shared_ptr<Entity> Builtins::class_func(new Class(((Class *)(Builtins::class_object.get()))->env));
    const std::shared_ptr<Entity> Builtins::class_system(new Class(((Class *)(Builtins::class_object.get()))->env));
}