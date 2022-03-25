#ifndef CONCEPT_H
#define CONCEPT_H

#include <string>
#include <vector>
#include <sstream>
#include <functional>

#include "env.h"
#include "entity.h"
#include "arguments.h"

namespace pluto
{
    using func_t = std::function<std::shared_ptr<Entity>(std::shared_ptr<Arguments>)>;

    class Object : public Entity
    {
    public:
        std::shared_ptr<Env> env;
        std::string string_val;
        std::vector<std::shared_ptr<Entity> > collection_elems;
        func_t func;
        std::shared_ptr<Entity> super;

        Object();
        Object(std::shared_ptr<Env> env);
        Object(std::shared_ptr<Env> env, std::string string_val);
        Object(std::shared_ptr<Env> env, func_t func);
        Object(std::shared_ptr<Env> env, std::vector<std::shared_ptr<Entity> > collection_elems);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> super);
        bool is_true();
        EntityKind kind();
        std::string to_string();
    };
}

#endif