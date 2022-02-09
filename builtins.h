#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>
#include <map>
#include <functional>

#include "nodes.h"
#include "objects.h"
#include "scopes.h"
#include "arguments.h"

namespace Builtins {
    class Utility {
        public:
            static Entities::Object *class_Object;
            static Entities::Object *class_Function;

            static Entities::Object *func_printLine;
    };
}

#endif // BUILTINS_H