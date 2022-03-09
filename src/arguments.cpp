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

    std::shared_ptr<Entity> Arguments::at(int idx)
    {
        if (idx >= data.size())
        {
            return Nil::NIL;
        }

        return data.at(idx);
    }
}