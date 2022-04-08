#include <string>

#include "location.h"

namespace pluto
{
    Location::Location(int idx, int line, int col)
        : idx(idx), line(line), col(col)
    {
    }

    Location Location::clone() const
    {
        return Location(idx, line, col);
    }

    std::string Location::repr() const
    {
        return std::to_string(line) + ":" + std::to_string(col);
    }

} // namespace pluto