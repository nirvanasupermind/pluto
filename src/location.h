#ifndef LOCATION_H
#define LOCATION_H

#include <string>

namespace pluto
{
    // Location - Index, line and column in the program.

    class Location
    {
    public:
        int idx;
        int line;
        int col;
        Location(int idx, int line, int col);
        std::string str() const;
    };

} // namespace pluto

#endif // LOC_H