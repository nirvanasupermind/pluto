#ifndef ENV_H
#define ENV_H

#include <string>
#include <memory>
#include <map>

#include "entity.h"

namespace pluto
{
    class Env
    {
        public:
            std::map<std::string, std::shared_ptr<Entity> > map;
            std::shared_ptr<Env> parent;
            Env();
            Env(std::shared_ptr<Env> parent);
            void set(std::string key, std::shared_ptr<Entity> val);
            std::shared_ptr<Entity> get(std::string key);
            bool has(std::string key);
            Env *resolve(std::string key);
    };
}

#endif