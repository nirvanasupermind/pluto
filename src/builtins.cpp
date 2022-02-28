#include <string>
#include <memory>

#include "env.h"
#include "entity.h"
#include "concept.h"
#include "builtins.h"

namespace pluto
{
    std::unique_ptr<Entity> Builtins::class_object = std::move(std::unique_ptr<Entity>(new Class()));
    std::unique_ptr<Entity> Builtins::class_string = std::move(std::unique_ptr<Entity>(new Class(
        std::move(((Class *)(Builtins::class_object.get()))->env)
    )));
};