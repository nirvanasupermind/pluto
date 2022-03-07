#include <string>
#include <memory>
#include <map>

#include "entity.h"
#include "env.h"

namespace pluto
{
    Env::Env()
    {
    }

    Env::Env(std::shared_ptr<Env> parent)
    {
        this->parent = parent;
    }

    void Env::set(std::string key, std::shared_ptr<Entity> val, bool is_const)
    {
        map[key] = val;
        constness[key] = is_const;
    }

    std::shared_ptr<Entity> Env::get(std::string key)
    {
        if (map.count(key) == 0 && parent.get() != nullptr)
        {
            return parent.get()->get(key);
        }
        else
        {
            return map.at(key);
        }
    }

    bool Env::has(std::string key)
    {        
        if (map.count(key) == 0 && parent.get() != nullptr)
        {
            return parent.get()->has(key);
        }
        else
        {
            return map.count(key) == 1;
        }
    }

    Env *Env::resolve(std::string key)
    {        
        if (map.count(key) == 0)
        {
            return this->parent.get();
        } else {
            return this;
        }
    }
}