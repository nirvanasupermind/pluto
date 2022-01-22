#ifndef INTERPRETER_H
#define INTERPRETER_H

#define INSTANCEOF(x, t) dynamic_cast<t*>(x) != nullptr 

#include <string>

#include "nodes.h"
#include "values.h"

namespace Interpreter {
    class Interpreter {
        public:
            std::string filename;
            Interpreter(std::string);
            Values::Value *visit(Nodes::Node *);
            Values::Value *visit_add_node(Nodes::Node *);
            Values::Value *visit_subtract_node(Nodes::Node *);
            Values::Value *visit_multiply_node(Nodes::Node *);
            Values::Value *visit_divide_node(Nodes::Node *);
            Values::Value *visit_power_node(Nodes::Node *);
            Values::Value *visit_plus_node(Nodes::Node *);
            Values::Value *visit_minus_node(Nodes::Node *);
    };
}

#endif // INTERPRETER_H