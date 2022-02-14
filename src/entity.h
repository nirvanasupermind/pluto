#ifndef ENTITY_H
#define ENTITY_H

#include <string>

namespace pluto
{
    enum EntityKind
    {
        INT_ENTITY,
        DOUBLE_ENTITY,
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
}

#endif