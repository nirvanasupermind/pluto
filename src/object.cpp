#include <string>
#include <sstream>

#include "object.h"
#include "env.h"

namespace pluto
{
    Object::Object()
    {
        is_string = false;
    }

    Object::Object(std::unique_ptr<Env> env)
    {
        this->env = std::move(env);
        is_string = false;
    }

    Object::Object(std::unique_ptr<Env> env, std::string string_val)
    {
        this->env = std::move(env);
        is_string = true;
    }

    EntityKind Object::kind() {
        return OBJECT_ENTITY;
    }
    
    std::string Object::to_string() {
        if(is_string) {
            return string_val;
        } else {
            std::ostringstream oss;
            oss << (void*)this;
            std::string s(oss.str());

            return s;
        }
    }
}