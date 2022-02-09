#include "arguments.h"

namespace Arguments {
    Arguments::Arguments(std::string filename, int line, std::vector<Entities::Entity *> args) {
        this->filename = filename;
        this->line = line;
        this->args = args;
    }

    Entities::Entity *Arguments::get(int n) {
        if(args.size() <= n) {
            return new Entities::Nil();
        } else {
            return args[n];
        }
    }

    Entities::Entity *Arguments::last() {
        if(args.size() == 0) {
            return new Entities::Nil();
        } else {
            return args.back();
        }
    }
}