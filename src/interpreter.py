from src.null import Null

class Interpreter:
    def __init__(self, path):
        self.path = path

    def raise_error(self, msg):
        raise SystemExit(f'{self.path}: {msg}')

    def visit(self, node):
        method_name = f'visit_{node[0]}_node'
        method = getattr(self, method_name)
        return method(node)

    def visit_empty_node(self, node):
        return Null()

    def visit_number_node(self, node):
        return node[1]

    def visit_add_node(self, node):
        try:
            return self.visit(node[1]) + self.visit(node[2])
        except TypeError:
            self.raise_error('invalid operation')
    
    def visit_subtract_node(self, node):
        try:
            return self.visit(node[1]) - self.visit(node[2])
        except TypeError:
            self.raise_error('invalid operation')

    def visit_multiply_node(self, node):
        try:
            return self.visit(node[1]) * self.visit(node[2])
        except TypeError:
            self.raise_error('invalid operation')

    def visit_divide_node(self, node):
        try:
            return self.visit(node[1]) / self.visit(node[2])
        except TypeError:
            self.raise_error('invalid operation')

    def visit_plus_node(self, node):
        try:
            return +self.visit(node[1])
        except TypeError:
            self.raise_error('invalid operation')

    def visit_minus_node(self, node):
        try:
            return -self.visit(node[1])
        except TypeError:
            self.raise_error('invalid operation')
    
    def visit_statements_node(self, node):
        if len(node) == 0: 
            return Null()
        
        for i in range(1, len(node) - 1):
            self.visit(node[i])
        
        return self.visit(node[-1])