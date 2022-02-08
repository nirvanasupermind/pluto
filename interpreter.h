#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>

#include "nodes.h"
#include "entities.h"
#include "scopes.h"

namespace Interpreter {
    class Interpreter {
        public:
            std::string filename;
            Interpreter(std::string);
            Entities::Entity *visit(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_symbol_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_add_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_subtract_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_multiply_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_divide_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_power_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_plus_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_minus_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_lt_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_gt_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_le_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_ge_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_ee_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_ne_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_or_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_and_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_xor_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_not_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_bitor_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_bitand_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_bitxor_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_bitnot_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_lshift_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_rshift_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_eq_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_var_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_block_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_if_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_if_else_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_for_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_while_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_function_node(Nodes::Node *, Scopes::Scope *);
            Entities::Entity *visit_file_node(Nodes::Node *, Scopes::Scope *);
    };
}

#endif // INTERPRETER_H