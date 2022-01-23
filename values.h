#ifndef VALUES_H
#define VALUES_H

#include <string>
#include <cstdint>

namespace Values {
    class Value {
        public:
            virtual std::string to_string() = 0;
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
}

#endif // VALUES_H