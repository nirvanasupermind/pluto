#include <string>

namespace pluto {
    class Token {
        public:
            int line;
            std::string type;
            std::string value;

            Token(int line, std::string type) {
                this->line = line;
                this->type = type;
            }
            
            Token(int line, std::string type, std::string value) {
                this->line = line;
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