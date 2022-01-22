#include <iostream>
#include <cstdint>

#include "values.h"

namespace Values {
    Byte::Byte(signed char byte) {
        this->byte = byte;
    }

    std::string Byte::to_string() {
        return std::to_string((int)byte);
    }

    Number::Number(double value) {
        this->value = value;
    }

    std::string Number::to_string() {
        return std::to_string(value);
    }

    // void print_number(Number& number) {
    //     std::cout << static_cast<std::string>(number) << "\n";
    // }
}