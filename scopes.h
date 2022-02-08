#ifndef SCOPES_H
#define SCOPES_H

#include <string>
#include <map>

#include "nodes.h"
#include "entities.h"

namespace Scopes {
    class Scope {
        public:
            Scope *parent;
            std::map<std::string, Entities::Entity *> map;

            Scope();
            Scope(Scope *parent);

            Entities::Entity *get(std::string name);
            void set(std::string name, Entities::Entity *value);
            Scopes::Scope *resolve(std::string name);

            void add_builtins();
    };
}

#endif // SCOPES_H