#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>

#include "nodes.h"
#include "values.h"
#include "scopes.h"

namespace Interpreter {
    class Interpreter {
        public:
            std::string filename;
            Interpreter(std::string);
            Values::Value *visit(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_symbol_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_add_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_subtract_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_multiply_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_divide_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_power_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_plus_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_minus_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_lt_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_gt_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_le_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_ge_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_ee_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_ne_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_or_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_and_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_xor_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_not_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_bitor_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_bitand_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_bitxor_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_bitnot_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_lshift_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_rshift_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_eq_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_var_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_block_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_if_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_if_else_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_for_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_while_node(Nodes::Node *, Scopes::Scope *);
            Values::Value *visit_file_node(Nodes::Node *, Scopes::Scope *);
    };
}

#endif // INTERPRETER_H