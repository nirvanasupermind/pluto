from src.symbol import Symbol
from src.env import Env
from src.global_env import global_env
from src.util import is_true
from src.object import Object

class Interpreter:
    def __init__(self, path):
        self.path = path
        self.should_return = False

    def raise_error(self, msg):
        raise SystemExit(f'{self.path}: {msg}')

    def visit(self, node, env):
        method_name = f'visit_{node[0]}_node'
        method = getattr(self, method_name)
        return method(node, env)

    def visit_empty_node(self, node, env):
        return Symbol('null')

    def visit_number_node(self, node, env):
        return node[1]

    def visit_name_node(self, node, env):
        result = env.get(node[1])

        if result == None:
            self.raise_error(f'{node[1]} is not defined')
        
        return result

    def visit_member_node(self, node, env):
        obj = self.visit(node[1], env)

        result = obj.env.get(node[2])

        if result == None:
            self.raise_error(f'{node[2]} is not defined')
        
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

    def visit_call_node(self, node, env):
        function = self.visit(node[1], env)

        if not isinstance(function, Object): 
            self.raise_error(f'{function} is not an object')

        args = []

        for arg_node in node[2]:
            args.append(self.visit(arg_node, env))

        try:
            if node[1][0] == 'member':
                return function.primitive_value(args, self.visit(node[1][1], env))

            return function.primitive_value(args, None)
        except TypeError:
            self.raise_error('invalid operation')

    def visit_new_node(self, node, env):
        cls = self.visit(node[1], env)

        if not isinstance(cls, Object): 
            self.raise_error(f'{cls} is not an object')

        args = []

        for arg_node in node[2]:
            args.append(self.visit(arg_node, env))

        obj = Object()
    
        obj.env.parent = cls.env

        if cls.env.has('constructor'):
            constructor = cls.env.get('constructor')
            if not isinstance(constructor, Object): 
                self.raise_error(f'{constructor} is not an object')

            try:
                constructor.primitive_value(args, obj)
            except TypeError:
                self.raise_error('invalid operation')
        
        return obj

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

    def visit_assign_node(self, node, env): 
        if node[1][0] == 'member':   
            obj = self.visit(node[1][1], env)

            if not isinstance(obj, Object): 
                self.raise_error(f'{obj} is not an object')

            name = node[1][2]

            value = self.visit(node[2], env)

            return obj.env.set(name, value)
        else:     
            if node[1][0] != 'name':
                self.raise_error('invalid left-hand side in assignment')

            name = node[1][1]
            value = self.visit(node[2], env)

            return env.set(name, value)

    def visit_block_node(self, node, env):
        block_env = Env(parent=env)

        if len(node) == 0: 
            return Symbol('null')
        
        self.should_return = False

        for i in range(1, len(node)):
            result = self.visit(node[i], block_env)
            if self.should_return:
                return result        

        return Symbol('null')

    def visit_if_node(self, node, env):
        condition = self.visit(node[1], env)

        if is_true(condition):
            return self.visit(node[2], env)
        else:
            return Symbol('null')

    def visit_if_else_node(self, node, env):
        condition = self.visit(node[1], env)

        if is_true(condition):
            return self.visit(node[2], env)
        else:
            return self.visit(node[3], env)

    def visit_while_node(self, node, env):
        condition = self.visit(node[1], env)

        while is_true(condition):
            self.visit(node[2], env)

        return Symbol('null')

    def visit_anonymous_function_node(self, node, env):
        def function(args, this):
            function_env = Env(parent=env)

            if this != None:
                function_env.set('this', this)

            for i in range(0, len(node[1])):
                arg = args[i] if i < len(args) else Symbol('null')
                function_env.set(node[1][i].value, arg)

            return self.visit(node[2], function_env)
        
        return Object(function)

    def visit_function_node(self, node, env):
        def function(args, this):
            function_env = Env(parent=env)

            if this != None:
                function_env.set('this', this)

            for i in range(0, len(node[2])):
                arg = args[i] if i < len(args) else Symbol('null')
                function_env.set(node[2][i].value, arg)

            return self.visit(node[3], function_env)
        
        result =  Object(function)
        result.env.parent = global_env.get('Function')
        
        return env.set(node[1], Object(function))

    def visit_anonymous_class_node(self, node, env):
        result = Object()

        class_env = Env(parent=global_env.get('Object').env)
        
        block_env = Env(parent=env)

        if len(node) == 0: 
            return Symbol('null')
        
        self.should_return = False

        for i in range(1, len(node[1])):
            result = self.visit(node[1][i], block_env)
            if self.should_return:
                return result        

        class_env.record.update(block_env.record)

        cls = Object()
        cls.env = class_env

        return cls


    def visit_class_node(self, node, env):
        result = Object()

        class_env = Env(parent=global_env.get('Object').env)
        
        block_env = Env(parent=env)

        if len(node) == 0: 
            return Symbol('null')
        
        self.should_return = False

        for i in range(1, len(node[2])):
            result = self.visit(node[2][i], block_env)
            if self.should_return:
                return result        

        class_env.record.update(block_env.record)

        cls = Object()
        cls.env = class_env

        env.set(node[1], cls)

        return cls

    def visit_return_node(self, node, env):
        self.should_return = True
        return self.visit(node[1], env)

    def visit_statements_node(self, node, env):
        if len(node) == 0: 
            return Symbol('null')
        
        for i in range(1, len(node) - 1):
            self.visit(node[i], env)      

        return self.visit(node[-1], env)