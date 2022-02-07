#include "entities.h"
#include "arguments.h"

namespace Arguments {
    Args::Args(std::string filename, int line, std::vector<Entities::Entity *> args) {
        this->filename = filename;
        this->line = line;
        this->args = args;
    }

    Entities::Entity *Args::get(int n) {
        if(args.size() <= n) {
            return new Entities::Nil();
        } else {
            return args[n];
        }
    }

    Entities::Entity *Args::last() {
        if(args.size() == 0) {
            return new Enttiies::Nil();
        } else {
            return args.back();
        }
    }
}