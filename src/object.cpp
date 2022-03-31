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
        name = "(?)";
    }

    Object::Object(std::string name)
    {
        this->env = std::shared_ptr<Env>(new Env());
        this->name = name;
    }

    Object::Object(std::shared_ptr<Env> env)
    {
        this->env = env;
        name = "(?)";
    }


    Object::Object(std::shared_ptr<Env> env, std::string name)
    {
        this->env = env;
        this->name = name;
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type)
    {
        this->env = env;
        this->type = type;
        name = "(?)";
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::string string_val,  bool is_name)
    {
        this->env = env;
        this->type = type;
        if(is_name) {
            this->name = string_val;
        } else {
            this->string_val = string_val;
            name = "(?)";
        }
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, std::vector<std::shared_ptr<Entity> > elems)
    {
        this->env = env;
        this->type = type;
        this->elems = elems;
        name = "(?)";
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, func_t func)
    {
        this->env = env;
        this->type = type;
        this->func = func;
        name = "(?)";
    }

    Object::Object(std::shared_ptr<Env> env, std::shared_ptr<Entity> type, func_t func, std::string name)
    {
        this->env = env;
        this->type = type;
        this->func = func;
        this->name = name;
        name = "(?)";
    }

    EntityKind Object::kind()
    {
        return OBJECT_ENTITY;
    }

    bool Object::is_true()
    {
        return true;
    }

    bool Object::has_func(std::string filename, int line, std::string name)
    {
        std::shared_ptr<Env> my_env = nullptr;

        if (type != nullptr && type->kind() == OBJECT_ENTITY)
        {
            std::shared_ptr<Object> type_obj = std::static_pointer_cast<Object>(type);
            if (type_obj->env->has(name))
            {
                my_env = type_obj->env;
            }
        }

        if (env->has(name))
        {
            my_env = env;
        }

        if (my_env != nullptr)
        {
            func_t func = ((Object *)((my_env->get(name)).get()))->func;

            if (func)
            {
                return true;
            }
        }

        return false;
    }

    std::string Object::str()
    {
        std::stringstream oss;
        oss << (void *)this;
        std::string s(oss.str());

        return s;
    }

    std::string Object::advanced_str(std::string filename, int line)
    {
        std::shared_ptr<Arguments> tostring_args(new Arguments(filename, line, std::vector<std::shared_ptr<Entity> >()));
        tostring_args->self = shared_from_this();

        std::shared_ptr<Entity> res = std::static_pointer_cast<Object>(env->get("toString"))->func(tostring_args);

        if (res->kind() == OBJECT_ENTITY)
        {
            return std::static_pointer_cast<Object>(res)->string_val;
        }

        return str();
    }
}