#ifndef VALUES_H
#define VALUES_H

#include <string>

namespace pluto
{

    class Number
    {
    public:
        double value;

        Number(double value) : value(value) {}

        std::string str() const;
    };

} // namespace pluto

#endif // VALUES_H