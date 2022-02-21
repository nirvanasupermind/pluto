#include <string>
#include <memory>

#include "env.h"
#include "entity.h"
#include "concept.h"
#include "builtins.h"

namespace pluto
{
    const std::unique_ptr<Class> Builtins::class_object = std::move(std::unique_ptr<Class>(new Class()));
    const std::unique_ptr<Class> Builtins::class_string = std::move(std::unique_ptr<Class>(new Class()));
};