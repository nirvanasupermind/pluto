#include <string>

#include "entity.h"

namespace pluto
{
    Int::Int(int int_val)
    {
        this->int_val = int_val;
    }

    EntityKind Int::kind()
    {
        return INT_ENTITY;
    }

    std::string Int::to_string()
    {
        return std::to_string(int_val);
    }

    Double::Double(double double_val)
    {
        this->double_val = double_val;
    }

    EntityKind Double::kind()
    {
        return DOUBLE_ENTITY;
    }

    std::string Double::to_string()
    {
        return std::to_string(double_val);
    }
}