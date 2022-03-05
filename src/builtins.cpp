#include <string>
#include <memory>
#include <iostream>

#include "env.h"
#include "entity.h"
#include "concept.h"
#include "builtins.h"

namespace pluto
{
    const std::shared_ptr<Entity> Builtins::class_object = std::shared_ptr<Entity>(new Class());
    const std::shared_ptr<Entity> Builtins::class_string = std::shared_ptr<Entity>(new Class(((Class *)(Builtins::class_object.get()))->env));
}