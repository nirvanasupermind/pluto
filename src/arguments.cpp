#include <string>
#include <memory>
#include <vector>

#include "entity.h"
#include "arguments.h"

namespace pluto
{
    Arguments::Arguments(std::string filename, int line, std::vector<std::shared_ptr<Entity> > data)
    {
        this->filename = filename;
        this->line = line;
        this->data = data;
    }

    std::shared_ptr<Entity> Arguments::at(int idx, std::string func_name)
    {
        if (idx >= data.size())
        {
            throw std::string(filename + ":" + std::to_string(line) + ": missing argument #"+std::to_string(data.size() + 1) + " to function '"+func_name+"'");
        }

        return data.at(idx);
    }
}