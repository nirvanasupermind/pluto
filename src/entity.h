#ifndef ENTITY_H
#define ENTITY_H

#include <string>

namespace pluto
{
    enum EntityKind
    {
        BYTE_ENTITY,
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
        virtual bool is_true() = 0;

        virtual EntityKind kind() = 0;
        
        virtual std::string to_string() = 0;
    };

    class Byte : public Entity
    {
    public:
        signed char byte_val;

        Byte(signed char byte_val);

        bool is_true();

        EntityKind kind();

        std::string to_string();
    };

    class Int : public Entity
    {
    public:
        long int int_val;

        Int(long int int_val);

        bool is_true();

        EntityKind kind();

        std::string to_string();
    };

    class Double : public Entity
    {
    public:
        double double_val;

        Double(double double_val);

        bool is_true();

        EntityKind kind();

        std::string to_string();
    };

    class Bool : public Entity
    {
    public:
        static const std::shared_ptr<Entity> TRUE;
        static const std::shared_ptr<Entity> FALSE;

        bool bool_val;

        Bool(bool bool_val);

        bool is_true();

        EntityKind kind();

        std::string to_string();
    };

    class Nil : public Entity
    {
    public:
        static const std::shared_ptr<Entity> NIL;

        Nil();

        bool is_true();

        EntityKind kind();

        std::string to_string();
    };
}

#endif