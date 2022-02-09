#include "builtins.h"

namespace Builtins {
    Entities::Object *Utility::class_Object = new Entities::Object();
    Entities::Object *Utility::class_Function = new Entities::Object(Utility::class_Object);
    Entities::Object *Utility::func_printLine = new Entities::Object(Utility::class_Function, [](Arguments::Arguments *args) {
        std::cout << args->get(0)->to_string() << '\n';
        return new Entities::Nil();
    });
} 