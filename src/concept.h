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
        std::shared_ptr<Env> env;
        std::string string_val;
        func_t func;

        Object() : Concept() {};

        Object(std::shared_ptr<Env> env) : Concept(env) {};

        Object(std::shared_ptr<Env> env, std::string string_val);

        Object(std::shared_ptr<Env> env, func_t func);

        EntityKind kind();

        std::string to_string();
    };

    class Class : public Concept
    {
    public:
        std::shared_ptr<Env> env;

        Class() : Concept() {};

        Class(std::shared_ptr<Env> env) : Concept(env) {};

        EntityKind kind();

        std::string to_string();
    };

    class Module : public Concept
    {
    public:
        std::shared_ptr<Env> env;

        Module() : Concept() {};

        Module(std::shared_ptr<Env> env) : Concept(env) {};

        EntityKind kind();

        std::string to_string();
    };
}

#endif