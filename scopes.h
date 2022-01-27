#ifndef SCOPES_H
#define SCOPES_H

#include <string>
#include <map>

#include "nodes.h"
#include "values.h"

namespace Scopes {
    class Scope {
        public:
            Scope *parent;
            std::map<std::string, Values::Value *> map;

            Scope();
            Scope(Scope *parent);

            Values::Value *get(std::string name);
            void set(std::string name, Values::Value *value);
    };
}

#endif // SCOPES_H