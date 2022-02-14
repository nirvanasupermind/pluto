#include <string>
#include <memory>

#include "env.h"
#include "entity.h"
#include "object.h"
#include "builtins.h"

namespace pluto
{   
    const std::unique_ptr<Object> Builtins::class_object = std::move(std::unique_ptr<Object>(new Object()));
    const std::unique_ptr<Object> Builtins::class_string = std::move(std::unique_ptr<Object>(new Object()));
};