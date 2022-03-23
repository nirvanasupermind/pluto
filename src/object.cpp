#include <string>
#include <sstream>
#include <functional>

#include "env.h"
#include "entity.h"
#include "object.h"

namespace pluto
{
    Object::Object()
    {
        this->env = std::shared_ptr<Env>(new Env());
    }

    Object::Object(std::shared_ptr<Env> env)
    {
        this->env = env;
    }

    Object::Object(std::shared_ptr<Env> env, std::string string_val)
    {
        this->env = env;
        this->string_val = string_val;
    }

    Object::Object(std::shared_ptr<Env> env, func_t func)
    {
        this->env = env;
        this->func = func;
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> super)
    {
        this->env = env;
        this->super = super;
    }

    EntityKind Object::kind()
    {
        return OBJECT_ENTITY;
    }

    bool Object::is_true()
    {
        return true;
    }

    std::string Object::to_string()
    {
        std::ostringstream oss;
        oss << (void *)this;
        std::string s(oss.str());

        return "(object : " + s + ")";
    }
}