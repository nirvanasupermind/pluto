#include <iostream>
#include <cstdint>

#include "values.h"

namespace Values {
    std::string Nil::to_string() {
        return std::string("nil");
    }

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

    Bool::Bool(bool bool_) {
        this->bool_ = bool_;
    }

    std::string Bool::to_string() {
        return (bool_ ? "true" : "false");
    }
}