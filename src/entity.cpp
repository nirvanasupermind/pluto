#include <string>

#include "entity.h"

namespace pluto
{
    Byte::Byte(signed char byte_val)
    {
        this->byte_val = byte_val;
    }

    bool Byte::is_true()
    {
        return true;
    }

    EntityKind Byte::kind()
    {
        return BYTE_ENTITY;
    }

    std::string Byte::to_string()
    {
        return std::to_string((int)byte_val);
    }

    Int::Int(long int int_val)
    {
        this->int_val = int_val;
    }

    bool Int::is_true()
    {
        return true;
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

    bool Double::is_true()
    {
        return true;
    }

    EntityKind Double::kind()
    {
        return DOUBLE_ENTITY;
    }

    std::string Double::to_string()
    {
        return std::to_string(double_val);
    }

    Bool::Bool(bool bool_val)
    {
        this->bool_val = bool_val;
    }

    bool Bool::is_true()
    {
        return bool_val;
    }

    EntityKind Bool::kind()
    {
        return BOOL_ENTITY;
    }
    
    std::string Bool::to_string()
    {
        return (bool_val ? "true": "false");
    }

    Nil::Nil()
    {
    }

    bool Nil::is_true()
    {
        return false;
    }

    EntityKind Nil::kind()
    {
        return NIL_ENTITY;
    }

    std::string Nil::to_string()
    {
        return "nil";
    }

    const std::shared_ptr<Entity> Nil::NIL(new Nil());
}