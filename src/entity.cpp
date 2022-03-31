#include <string>

#include "entity.h"

namespace pluto
{
    std::string error_desc(EntityKind kind, bool article)
    {
        if (article)
        {
            switch (kind)
            {
            case NIL_ENTITY:
                return "nil";
            case INT_ENTITY:
                return "an int";
            case OBJECT_ENTITY:
                return "an object";
            default:
                return "a " + error_desc(kind);
            }
        }

        switch (kind)
        {
        case INT_ENTITY:
            return "int";
        case DOUBLE_ENTITY:
            return "double";
        case CHAR_ENTITY:
            return "char";
        case BOOL_ENTITY:
            return "bool";
        case NIL_ENTITY:
            return "nil";
        case OBJECT_ENTITY:
            return "object";
        }
    }

    Int::Int(std::int32_t int_val)
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

    std::string Int::str()
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

    std::string Double::str()
    {
        return std::to_string(double_val);
    }

    Char::Char(unsigned char char_val)
    {
        this->char_val = char_val;
    }

    bool Char::is_true()
    {
        return true;
    }

    EntityKind Char::kind()
    {
        return CHAR_ENTITY;
    }

    std::string Char::str()
    {
        return std::string(1, char_val);
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

    std::string Bool::str()
    {
        return (bool_val ? "true" : "false");
    }

    const std::shared_ptr<Entity> Bool::TRUE(new Bool(true));

    const std::shared_ptr<Entity> Bool::FALSE(new Bool(false));

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

    std::string Nil::str()
    {
        return "nil";
    }

    const std::shared_ptr<Entity> Nil::NIL(new Nil());
}