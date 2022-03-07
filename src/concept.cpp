#include <string>
#include <sstream>
#include <functional>

#include "env.h"
#include "entity.h"
#include "concept.h"

namespace pluto
{
    Concept::Concept()
    {
        this->env = std::shared_ptr<Env>(new Env());
    }

    Concept::Concept(std::shared_ptr<Env> env)
    {
        this->env = env;
    }

    bool Concept::is_true()
    {
        return true;
    }

    Object::Object(std::shared_ptr<Env> env, std::string string_val) {
        this->env = env;
        this->string_val = string_val;
    }

    EntityKind Object::kind() {
        return OBJECT_ENTITY;
    }
    
    std::string Object::to_string() {
        std::ostringstream oss;
        oss << (void*)this;
        std::string s(oss.str());

        return "(object : "+s+")";
    }

    EntityKind Class::kind() {
        return CLASS_ENTITY;
    }
    
    std::string Class::to_string() {
        std::ostringstream oss;
        oss << (void*)this;
        std::string s(oss.str());

        return "(class : "+s+")";
    }

    EntityKind Module::kind() {
        return MODULE_ENTITY;
    }
    
    std::string Module::to_string() {
        std::ostringstream oss;
        oss << (void*)this;
        std::string s(oss.str());

        return "(class : "+s+")";
    }
}