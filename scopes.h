#ifndef SCOPES_H
#define SCOPES_H

#include <string>
#include <map>

#include "nodes.h"
#include "values.h"

namespace Interpreter {
    class Scope {
        public:
            Scope *parent;
            std::map<std::string, Value *> map;

            Scope();
            Scope(Scope *parent);

            Value *get(std::string name);
            void set(std::string name, std::string value);
    };
}

#endif // SCOPES_H