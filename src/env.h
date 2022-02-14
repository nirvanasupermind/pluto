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
            std::map<std::string, std::unique_ptr<Entity> > map;
            std::unique_ptr<Env> parent;

            Env();
            Env(std::unique_ptr<Env> parent);

            void set(std::string key, std::unique_ptr<Entity> val);
            std::unique_ptr<Entity> get(std::string key);
            bool has(std::string key);
    };
}

#endif