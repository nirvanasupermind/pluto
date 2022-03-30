#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <cstdint>

namespace pluto
{
    enum EntityKind
    {
        INT_ENTITY,
        DOUBLE_ENTITY,
        CHAR_ENTITY,
        BOOL_ENTITY,
        NIL_ENTITY,
        OBJECT_ENTITY
    };
    
    std::string error_desc(EntityKind kind, bool article = false);

    class Entity
    {
    public:
        virtual bool is_true() = 0;

        virtual EntityKind kind() = 0;
        
        virtual std::string str() = 0;
    };

    class Int : public Entity
    {
    public:
        std::int32_t int_val;

        Int(std::int32_t int_val);

        bool is_true();

        EntityKind kind();

        std::string str();
    };

    class Double : public Entity
    {
    public:
        double double_val;

        Double(double double_val);

        bool is_true();

        EntityKind kind();

        std::string str();
    };

    class Char : public Entity
    {
    public:
        unsigned char char_val;

        Char(unsigned char char_val);

        bool is_true();

        EntityKind kind();

        std::string str();
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

        std::string str();
    };

    class Nil : public Entity
    {
    public:
        static const std::shared_ptr<Entity> NIL;

        Nil();

        bool is_true();

        EntityKind kind();

        std::string str();
    };
}

#endif