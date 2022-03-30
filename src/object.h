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
    
    class Object : public Entity, public std::enable_shared_from_this<Object>
    {
    public:
        std::shared_ptr<Env> env;
        std::string string_val;
        std::vector<std::shared_ptr<Entity> > elems;
        func_t func;
        std::shared_ptr<Entity> type;
    
        Object();
        Object(std::shared_ptr<Env> env);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::string string_val);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, func_t func);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::vector<std::shared_ptr<Entity> > elems);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type);
        bool is_true();
        EntityKind kind();
        std::string str();
        std::string advanced_str(std::shared_ptr<Arguments> args);
    };
}

#endif