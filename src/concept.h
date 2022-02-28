#ifndef CONCEPT_H
#define CONCEPT_H

#include <string>
#include <sstream>

#include "env.h"
#include "entity.h"

namespace pluto
{
    class Concept : public Entity
    {
    public:
        std::unique_ptr<Env> env;

        Concept();
        Concept(std::unique_ptr<Env> env);

        // std::string to_string();
    };

    class Object : public Concept
    {
    public:
        std::unique_ptr<Env> env;
        std::string string_val;

        Object() : Concept() {};

        Object(std::unique_ptr<Env> env) : Concept(std::move(env)) {};

        Object(std::unique_ptr<Env> env, std::string string_val);

        EntityKind kind();

        std::string to_string();
    };

    class Class : public Concept
    {
    public:
        std::unique_ptr<Env> env;

        Class() : Concept() {};

        Class(std::unique_ptr<Env> env) : Concept(std::move(env)) {};

        EntityKind kind();

        std::string to_string();
    };

    class Module : public Concept
    {
    public:
        std::unique_ptr<Env> env;

        Module() : Concept() {};

        Module(std::unique_ptr<Env> env) : Concept(std::move(env)) {};

        EntityKind kind();

        std::string to_string();
    };
}

#endif