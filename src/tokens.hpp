#include <string>

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
                if(this->value != "")
                    return type + ":" + value;
                
                return type;
            }
    };
};