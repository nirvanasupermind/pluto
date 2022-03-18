#ifndef CONCEPT_H
#define CONCEPT_H


#include <string>
#include <sstream>
#include <functional>

#include "env.h"
#include "entity.h"
#include "arguments.h"

namespace pluto
{
    using func_t = std::function<std::shared_ptr<Entity>(std::shared_ptr<Arguments>)>;

    class Concept : public Entity
    {
    public:
        std::shared_ptr<Env> env;

        Concept();
        Concept(std::shared_ptr<Env> env);

        bool is_true();
    };

    class Object : public Concept
    {
    public:
        std::string string_val;
        func_t func;
        std::shared_ptr<Entity> super;

        Object() : Concept() {};

        Object(std::shared_ptr<Env> env) : Concept(env) {};

        Object(std::shared_ptr<Env> env, std::string string_val);

        Object(std::shared_ptr<Env> env, func_t func);

        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> super);

        EntityKind kind();

        std::string to_string();
    };
}

#endif