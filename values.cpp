#include <string>

#include "values.h"

namespace pluto
{

    std::string Number::str() const
    {
        return std::to_string(value);
    }

} // namespace pluto