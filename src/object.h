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
        std::string name;
    
        Object();
        Object(std::string name);
        Object(std::shared_ptr<Env> env);
        Object(std::shared_ptr<Env> env, std::string name);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::string string_val, bool is_name = false);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, func_t func);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, func_t func, std::string name);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::vector<std::shared_ptr<Entity> > elems);
        Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type);
        std::shared_ptr<Entity> get(std::string key);
        bool is_true();
        EntityKind kind();
        bool has_func(std::string filename, int line, std::string name);
        std::string str();
        std::string advanced_str(std::string filename, int line);
    };
}

#endif