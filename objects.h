#ifndef OBJECTS_H
#define OBJECTS_H

#include <sstream>
#include <string>
#include <functional>

#include "scopes.h"
#include "arguments.h"

namespace Entities {
    using pluto_func = std::function<Entity *(Arguments::Arguments *)>;

    class Object: public Entity {
        public:
            Scopes::Scope *scope;
            pluto_func function;

            Object();
            Object(Object *parent);
            Object(Object *parent, pluto_func function);

            std::string to_string();

    };
}

#endif // OBJECTS_H