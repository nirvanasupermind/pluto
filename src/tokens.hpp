#include <string>
#include <vector>
#include <map>

namespace pluto {
    class Token {
        public:
            std::string type;
            std::string value;

            Token(std::string type) {
                this->type = type;
            }

            Token(std::string type, std::string value) {
                this->type = type;
                this->value = value;
            }

            operator std::string() const {
                if(value.empty())
                    return type;
                return type + ":" + value;
            }
    }; 
}