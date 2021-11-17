from src.null import Null

class Interpreter:
    def __init__(self, path):
        self.path = path

    def raise_error(self, msg):
        raise SystemExit(f'{self.path}: {msg}')

    def visit(self, node, env):
        method_name = f'visit_{node[0]}_node'
        method = getattr(self, method_name)
        return method(node, env)

    def visit_empty_node(self, node, env):
        return Null()

    def visit_number_node(self, node, env):
        return node[1]

    def visit_name_node(self, node, env):
        result = env.get(node[1], None)

        if result == None:
            self.raise_error(f'{node[1]} is not defined')
        
        return result

    def visit_add_node(self, node, env):
        try:
            return self.visit(node[1], env) + self.visit(node[2], env)
        except TypeError:
            self.raise_error('invalid operation')
    
    def visit_subtract_node(self, node, env):
        try:
            return self.visit(node[1], env) - self.visit(node[2], env)
        except TypeError:
            self.raise_error('invalid operation')

    def visit_multiply_node(self, node, env):
        try:
            return self.visit(node[1], env) * self.visit(node[2], env)
        except TypeError:
            self.raise_error('invalid operation')

    def visit_divide_node(self, node, env):
        try:
            return self.visit(node[1], env) / self.visit(node[2], env)
        except TypeError:
            self.raise_error('invalid operation')

    def visit_assign_node(self, node, env):
        if node[1][0] != 'name':
            self.raise_error('invalid left-hand side in assignment')
        
        name = node[1][1]
        value = self.visit(node[2], env)

        env[name] = value

        return value


    def visit_plus_node(self, node, env):
        try:
            return +self.visit(node[1], env)
        except TypeError:
            self.raise_error('invalid operation')

    def visit_minus_node(self, node, env):
        try:
            return -self.visit(node[1], env)
        except TypeError:
            self.raise_error('invalid operation')
    
    def visit_statements_node(self, node, env):
        if len(node) == 0: 
            return Null()
        
        for i in range(1, len(node) - 1):
            self.visit(node[i], env)
        
        return self.visit(node[-1], env)