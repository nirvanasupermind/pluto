#ifndef ENTITIES_H
#define ENTITIES_H

#define INSTANCEOF(x, t) dynamic_cast<t*>(x) != nullptr 

#include <string>

namespace Entities {
    class Entity {
        public:
            virtual std::string to_string() = 0;
            bool truthy();
    };

    class Nil: public Entity {
        public:
            std::string to_string();
    };

    class Byte: public Entity {
        public:
            signed char byte;
            
            Byte(signed char);

            std::string to_string();
    };

    class Number: public Entity {
        public:
            double value;
            
            Number(double);

            std::string to_string();
    };

    class Bool: public Entity {
        public:
            bool bool_;
            
            Bool(bool);

            std::string to_string();
    };
}

#endif // ENTITIES_H