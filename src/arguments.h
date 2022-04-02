#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <memory>
#include <vector>

#include "entity.h"

namespace pluto
{
    class Arguments
    {
    public:
        std::string filename;
        std::string func_name;
        int line;
        std::shared_ptr<Entity> self;
        std::vector<std::shared_ptr<Entity> > data;
        Arguments(std::string filename, int line, std::vector<std::shared_ptr<Entity> > data);
        Arguments(std::string filename, int line, std::vector<std::shared_ptr<Entity> > data, std::string func_name);

        std::shared_ptr<Entity> at(int idx);
    };
}

#endif