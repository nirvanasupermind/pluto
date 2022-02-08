#include <string>
#include <map>

#include "nodes.h"
#include "objects.h"
#include "scopes.h"

namespace Scopes {
    class Builtins {
        public:
            static Entities::Object *Type;
            static Entities::Object *Object(Type);
            static Entities::Object *Function(Object);
    }
}