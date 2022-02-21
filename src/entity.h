#ifndef ENTITY_H
#define ENTITY_H

#include <string>

namespace pluto
{
    enum EntityKind
    {
        INT_ENTITY,
        DOUBLE_ENTITY,
        BOOL_ENTITY,
        NIL_ENTITY,
        OBJECT_ENTITY,
        CLASS_ENTITY,
        MODULE_ENTITY
    };

    class Entity
    {
    public:
        virtual EntityKind kind() = 0;
        
        virtual std::string to_string() = 0;
    };

    class Int : public Entity
    {
    public:
        int int_val;

        Int(int int_val);

        EntityKind kind();

        std::string to_string();
    };

    class Double : public Entity
    {
    public:
        double double_val;

        Double(double double_val);

        EntityKind kind();

        std::string to_string();
    };

    class Bool : public Entity
    {
    public:
        bool bool_val;

        Bool(bool bool_val);

        EntityKind kind();

        std::string to_string();
    };

    class Nil : public Entity
    {
    public:
        Nil();

        EntityKind kind();

        std::string to_string();
    };
}

#endif