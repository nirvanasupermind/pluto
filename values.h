#ifndef VALUES_H
#define VALUES_H

#define INSTANCEOF(x, t) dynamic_cast<t*>(x) != nullptr 

#include <string>

namespace Values {
    class Value {
        public:
            virtual std::string to_string() = 0;
            bool truthy();
    };

    class Nil: public Value {
        public:
            std::string to_string();
    };

    class Byte: public Value {
        public:
            signed char byte;
            
            Byte(signed char);

            std::string to_string();
    };

    class Number: public Value {
        public:
            double value;
            
            Number(double);

            std::string to_string();
    };

    class Bool: public Value {
        public:
            bool bool_;
            
            Bool(bool);

            std::string to_string();
    };
}

#endif // VALUES_H