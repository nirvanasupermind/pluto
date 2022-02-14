#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <sstream>

#include "env.h"
#include "entity.h"

namespace pluto
{
    class Object : public Entity
    {
    public:
        std::unique_ptr<Env> env;
        std::string string_val;
        bool is_string;
        
        Object();
        Object(std::unique_ptr<Env> env);
        Object(std::unique_ptr<Env> env, std::string string_val);

        EntityKind kind();

        std::string to_string();
    };
}

#endif