#include <string>
#include <memory>
#include <iostream>

#include "env.h"
#include "entity.h"
#include "object.h"
#include "builtins.h"
#include "arguments.h"

namespace pluto
{
    const std::shared_ptr<Entity> Builtins::class_class(new Object("Class"));
    const std::shared_ptr<Env> Builtins::class_env = ((Object *)(Builtins::class_class.get()))->env;
    const std::shared_ptr<Entity> Builtins::class_object(new Object(std::shared_ptr<Env>(new Env()), Builtins::class_class, "Object", true));
    const std::shared_ptr<Env> Builtins::object_env = ((Object *)(Builtins::class_object.get()))->env;
    const std::shared_ptr<Entity> Builtins::class_string(new Object(std::shared_ptr<Env>(new Env(Builtins::object_env)), Builtins::class_class, "String", true));
    const std::shared_ptr<Entity> Builtins::class_list(new Object(std::shared_ptr<Env>(new Env(Builtins::object_env)), Builtins::class_class, "List", true));
    const std::shared_ptr<Entity> Builtins::class_func(new Object(std::shared_ptr<Env>(new Env(Builtins::object_env)), Builtins::class_class, "Func", true));
    const std::shared_ptr<Entity> Builtins::class_module(new Object(std::shared_ptr<Env>(new Env(Builtins::object_env)), Builtins::class_class, "Module", true));
    const std::shared_ptr<Entity> Builtins::class_math(new Object(std::shared_ptr<Env>(new Env(Builtins::object_env)), Builtins::class_class, "Math", true));

    const std::shared_ptr<Env> Builtins::string_env = ((Object *)(Builtins::class_string.get()))->env;
    const std::shared_ptr<Env> Builtins::list_env = ((Object *)(Builtins::class_list.get()))->env;
    const std::shared_ptr<Env> Builtins::func_env = ((Object *)(Builtins::class_func.get()))->env;
    const std::shared_ptr<Env> Builtins::module_env = ((Object *)(Builtins::class_module.get()))->env;
    const std::shared_ptr<Env> Builtins::math_env = ((Object *)(Builtins::class_math.get()))->env;

    const std::shared_ptr<Entity> Builtins::func_math_acos(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_string, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        if(akind == INT) {
            return std::shared_ptr<Entity>(new Double(std::acos(std::static_pointer_cast<Int>(a)->int_val)));
        } else if(akind == DOUBLE) {
            return std::shared_ptr<Entity>(new Double(std::acos(std::static_pointer_cast<Double>(a)->double_val)));
        } else {
             throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'acos' (int or double expected, got " + error_desc(akind) + ")");
        } },
        "acos"));

    const std::shared_ptr<Entity> Builtins::func_math_asin(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        if(akind == INT) {
            return std::shared_ptr<Entity>(new Double(std::asin(std::static_pointer_cast<Int>(a)->int_val)));
        } else if(akind == DOUBLE) {
            return std::shared_ptr<Entity>(new Double(std::asin(std::static_pointer_cast<Double>(a)->double_val)));
        } else {
            throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'asin' (int or double expected, got " + error_desc(akind) + ")");
        } },
        "asin"));

    const std::shared_ptr<Entity> Builtins::func_math_atan(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        if(akind == INT) {
            return std::shared_ptr<Entity>(new Double(std::atan(std::static_pointer_cast<Int>(a)->int_val)));
        } else if(akind == DOUBLE) {
            return std::shared_ptr<Entity>(new Double(std::atan(std::static_pointer_cast<Double>(a)->double_val)));
        } else {
            throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'atan' (int or double expected, got " + error_desc(akind) + ")");
        } },
        "atan"));

    const std::shared_ptr<Entity> Builtins::func_math_sqrt(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        if(akind == INT) {
            return std::shared_ptr<Entity>(new Double(std::sqrt(std::static_pointer_cast<Int>(a)->int_val)));
        } else if(akind == DOUBLE) {
            return std::shared_ptr<Entity>(new Double(std::sqrt(std::static_pointer_cast<Double>(a)->double_val)));
        } else {
            throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'atan' (int or double expected, got " + error_desc(akind) + ")");
        } },
        "sqrt"));

    const std::shared_ptr<Entity> Builtins::func_object_tostring(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        { 
            return std::shared_ptr<Entity>(new Object(std::shared_ptr<Env>(new Env()), Builtins::class_string, args->self->str()));
        },
        "toString"));

    const std::shared_ptr<Entity> Builtins::func_string_charat(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        std::string string_val = ((Object *)args->self.get())->string_val;
        int string_len = string_val.length();

        if(akind == INT) {
            int int_val = std::static_pointer_cast<Int>(a)->int_val;

            if(int_val >= string_len || int_val < 0) {
                throw std::string(args->filename + ":" + std::to_string(args->line) + ": string index out of range");
            }

            return std::shared_ptr<Entity>((new Char(string_val[int_val])));
        } else {
             throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'charAt' (int expected, got " + error_desc(akind) + ")");
        } },
        "charAt"));

    const std::shared_ptr<Entity> Builtins::func_string_first(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        return std::shared_ptr<Entity>(new Char(std::static_pointer_cast<Object>(args->self)->string_val.front())); },
        "first"));

    const std::shared_ptr<Entity> Builtins::func_string_last(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        return std::shared_ptr<Entity>(new Char(std::static_pointer_cast<Object>(args->self)->string_val.back())); },
        "last"));

    const std::shared_ptr<Entity> Builtins::func_string_length(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Object>(args->self)->string_val.size())); },
        "length"));

    const std::shared_ptr<Entity> Builtins::func_string_tostring(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        { 
            return args->self; 
        },
        "toString"));


    const std::shared_ptr<Entity> Builtins::func_list_get(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> a = args->at(0);
        EntityKind akind = a->kind();

        std::vector<std::shared_ptr<Entity> > elems = ((Object *)args->self.get())->elems;
        int size = elems.size();

        if(akind == INT) {
            int int_val = std::static_pointer_cast<Int>(a)->int_val;

            if(int_val >= size || int_val < 0) {
                throw std::string(args->filename + ":" + std::to_string(args->line) + ": list index out of range");
            }

            return elems.at(int_val);
        } else {
             throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'get' (int expected, got " + error_desc(akind) + ")");
        } },
        "get"));

    const std::shared_ptr<Entity> Builtins::func_list_set(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> a = args->at(0);
        std::shared_ptr<Entity> b = args->at(1);
        EntityKind akind = a->kind();

        std::shared_ptr<Object> self = std::static_pointer_cast<Object>(args->self);

        int size = self->elems.size();

        if(akind == INT) {
            int int_val = std::static_pointer_cast<Int>(a)->int_val;

            if(int_val >= size || int_val < 0) {
                throw std::string(args->filename + ":" + std::to_string(args->line) + ": list index out of range");
            }

            self->elems[int_val] = b;
            return Nil::NIL;
        } else {
             throw std::string(args->filename + ":" + std::to_string(args->line) + ": invalid argument #1 to 'get' (int expected, got " + error_desc(akind) + ")");
        } },
        "set"));


    const std::shared_ptr<Entity> Builtins::func_list_size(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        return std::shared_ptr<Entity>(new Int(std::static_pointer_cast<Object>(args->self)->elems.size())); },
        "size"));


    const std::shared_ptr<Entity> Builtins::func_list_tostring(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Object> self = std::static_pointer_cast<Object>(args->self);

        if(self->elems.size() == 0) {
            return std::shared_ptr<Entity>(new Object(std::shared_ptr<Env>(new Env()), Builtins::class_list, "[]"));
        }

        std::string result = "[";


        for (int i = 0; i < self->elems.size(); i++)
        {

            std::shared_ptr<Entity> elem = self->elems.at(i);

            std::string s = elem->str();

            if (elem->kind() == OBJECT_ENTITY)
            {
                s = ((Object *)elem.get())->advanced_str(args->filename, args->line);
            }

            result += s + ", ";
        }

        result.pop_back();
        result.pop_back();

        result += "]";
        return std::shared_ptr<Entity>(new Object(std::shared_ptr<Env>(new Env()), Builtins::class_list, result)); },
        "toString"));

    const std::shared_ptr<Entity> Builtins::func_print(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> arg = args->at(0);

        std::string s = arg->str();

        if (arg->kind() == OBJECT_ENTITY)
        {
            s = std::static_pointer_cast<Object>(arg)->advanced_str(args->filename, args->line);
        }

        std::cout << s;

        return Nil::NIL; },
        "print"));

    const std::shared_ptr<Entity> Builtins::func_println(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::shared_ptr<Entity> arg = args->at(0);

        std::string s = arg->str();

        if (arg->kind() == OBJECT_ENTITY)
        {
            s = std::static_pointer_cast<Object>(arg)->advanced_str(args->filename, args->line);
        }

        std::cout << s << '\n';

        return Nil::NIL; },
        "println"));

    const std::shared_ptr<Entity> Builtins::func_exit(new Object(
        std::shared_ptr<Env>(new Env()), Builtins::class_func, [](std::shared_ptr<Arguments> args)
        {
        std::exit(0);

        return Nil::NIL; },
        "exit"));
}