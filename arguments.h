#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <vector>

#include "entities.h"

namespace Arguments {
    class Args {
        public:
            std::string filename;
            int line;
            std::vector<Entities::Entity *> args;

            Args(std::string filename, std::vector<Entities::Enity *> args);

            Entities::Entity *get(int n);
            Entities::Entity *last();
    };
}

#endif // ARGUMENTS_H