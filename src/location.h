#ifndef LOCATION_H
#define LOCATION_H

#include <string>

namespace pluto
{
    // Location - Stores the index, line and column of a character in the source code. Useful for error messages.

    class Location
    {
    public:
        int idx;
        int line;
        int col;
        Location(int idx, int line, int col);
        ~Location() = default;
        Location clone() const; // Used in lexer
        std::string repr() const;
    };

} // namespace pluto

#endif // LOC_H