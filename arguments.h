#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <vector>

#include "entities.h"

namespace Arguments {
    class Arguments {
        public:
            std::string filename;
            int line;
            std::vector<Entities::Entity *> args;

            Arguments(std::string filename, int, std::vector<Entities::Entity *> args);

            Entities::Entity *get(int n);
            Entities::Entity *last();
    };
}

#endif // ARGUMENTS_H