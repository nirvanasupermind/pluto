#include <string>

namespace pluto {
    const int EOF_ = -1;
    const int NUMBER = -2;
    
    class Token {
        public:
            int ln;
            int type;
            double num_value;

            Token(int ln, int type) {
                this->ln = ln;
                this->type = type;
            }

            Token(int ln, int type, double num_value) {
                this->ln = ln;
                this->type = type;
                this->num_value = num_value;
            }

            operator std::string() const {
                if(type == NUMBER) 
                    return "(" + std::to_string(ln) + "," + std::to_string(type) + ","+std::to_string(num_value) + ")";

                return "(" + std::to_string(ln) + "," + std::to_string(type) +")";
            }
    };
}