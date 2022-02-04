#ifndef OBJECTS_H
#define OBJECTS_H

#define INSTANCEOF(x, t) dynamic_cast<t*>(x) != nullptr 

#include <string>

#include "entities.h"

namespace Entities {
    class Object: public Entity {
        public:
            Scopes::Scope *parent;
            Objects::Object();
            Objects::Object(Object *parent);
    };
}

#endif // OBJECTS_H