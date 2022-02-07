#include <sstream>

#include "entities.h"
#include "objects.h"

namespace Entities {
    Object::Object() {
        this->scope = new Scopes::Scope();
    }

    Object::Object(Object *parent) {
        if(parent == nullptr)
            this->scope = new Scopes::Scope();
        else
            this->scope = new Scopes::Scope(parent->scope);
    }
    
    std::string Object::to_string() {
        std::ostringstream oss;
        oss << (void*)this;
        std::string s(oss.str());

        return s;
    }
}