#include <string>;
#include <map>;

#include "nodes.h"
#include "values.h"
#include "scopes.h"

namespace Scopes {
    Scope::Scope() {
        parent = nullptr;
    }

    Scope::Scope(Scope *parent) {
        this->parent = parent;
    }

    Values::Value *Scope::get(std::string name) {
        if(map.count(name) == 0) {
            if(parent != nullptr)
                return parent->get(name);
            
            return nullptr;
        }

        return map[name];
    }

    void Scope::set(std::string name, Values::Value *value) {
        map[name] = value;
    }
}