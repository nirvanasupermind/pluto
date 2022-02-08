#include <string>
#include <map>

#include "nodes.h"
#include "entities.h"
#include "scopes.h"

namespace Scopes {
    Scope::Scope() {
        parent = nullptr;
    }

    Scope::Scope(Scope *parent) {
        this->parent = parent;
    }

    Entities::Entity *Scope::get(std::string name) {
        if(map.count(name) == 0) {
            if(parent != nullptr)
                return parent->get(name);
            
            return nullptr;
        }

        return map[name];
    }

    void Scope::set(std::string name, Entities::Entity *value) {
        map[name] = value;
    }

    Scopes::Scope *Scope::resolve(std::string name) {
        if(map.count(name) != 0)
            return this;
        
        if(parent == nullptr)
            return nullptr;

        return parent->resolve(name);
    }
}