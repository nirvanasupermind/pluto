#include <string>
#include <sstream>
#include <functional>

#include "env.h"
#include "entity.h"
#include "object.h"

namespace pluto
{
    Object::Object()
    {
        this->env = std::shared_ptr<Env>(new Env());
    }

    Object::Object(std::shared_ptr<Env> env)
    {
        this->env = env;
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type)
    {
        this->env = env;
        this->type = type;
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::string string_val)
    {
        this->env = env;
        this->type = type;
        this->string_val = string_val;
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::vector<std::shared_ptr<Entity> > elems)
    {
        this->env = env;
        this->type = type;
        this->elems = elems;
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, func_t func)
    {
        this->env = env;
        this->type = type;
        this->func = func;
    }

    EntityKind Object::kind()
    {
        return OBJECT_ENTITY;
    }

    bool Object::is_true()
    {
        return true;
    }

    std::string Object::str()
    {
        std::stringstream oss;
        oss << (void *)this;
        std::string s(oss.str());

        return s;
    }

    std::string Object::advanced_str(std::shared_ptr<Arguments> args)
    {
        std::string s = str();

        std::shared_ptr<Env> my_env = env;

        if (type != nullptr && type->kind() == OBJECT_ENTITY)
        {
            std::shared_ptr<Object> type_obj = std::static_pointer_cast<Object>(type);
            if (type_obj->env->has("toString"))
            {
                my_env = type_obj->env;
            }
        }

        if (my_env->has("toString"))
        {
            func_t func = ((Object *)((my_env->get("toString")).get()))->func;

            if (func)
            {
                std::shared_ptr<Arguments> tostring_args(new Arguments(args->filename, args->line, std::vector<std::shared_ptr<Entity> >()));
                tostring_args->self = shared_from_this();

                std::shared_ptr<Entity> res = func(tostring_args);

                if (res->kind() == OBJECT_ENTITY)
                {
                    s = ((Object *)res.get())->string_val;
                }
            }
        }

        return s;
    }
}