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
        OBJECT_ENTITY
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
        static std::unique_ptr<Entity> TRUE;
        static std::unique_ptr<Entity> FALSE;

        bool bool_val;

        Bool(bool bool_val);

        EntityKind kind();

        std::string to_string();
    };
}

#endif