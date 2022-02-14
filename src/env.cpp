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

    Env::Env(std::unique_ptr<Env> parent)
    {
        this->parent = std::move(parent);
    }

    void Env::set(std::string key, std::unique_ptr<Entity> val)
    {
        map[key] = std::move(val);
    }

    std::unique_ptr<Entity> Env::get(std::string key)
    {
        if (map.count(key) == 0 && parent.get() != nullptr)
        {
            return parent.get()->get(key);
        }
        else
        {
            return std::move(map[key]);
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
            return true;
        }
    }
}