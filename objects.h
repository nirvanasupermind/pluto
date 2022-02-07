#ifndef OBJECTS_H
#define OBJECTS_H

#include <sstream>
#include <string>
#include <functional>

#include "scopes.h"

namespace Entities {
    class Object: public Entity {
        public:
            Scopes::Scope *scope;
            // std::function<Args>

            Object();
            Object(Object *parent);

            std::string to_string();

    };
}

#endif // OBJECTS_H