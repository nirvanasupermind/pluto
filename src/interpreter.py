import numpy as np
from pathlib import Path
from src.lexer import Lexer
from src.parser import Parser
from src.symbol import Symbol
from src.char import Char
from src.env import Env
from src.global_env import global_env
from src.object import Object
from src.std import IllegalArgument, IndexOutOfRange, NoThis

STANDARD_MODULES = {
    'map': './modules/map.pluto'
}

class Interpreter:
    def __init__(self, path):
        self.path = path
        self.should_return = False

    def name_does_not_exist(self, name):
        raise SystemExit(f'{self.path}: name "{name}" does not exist')        

    def member_does_not_exist(self, member):
        raise SystemExit(f'{self.path}: member "{member}" does not exist')        

    def illegal_operation(self):
        raise SystemExit(f'{self.path}: illegal operation')

    def raise_error(self):
        raise SystemExit(f'{self.path}: runtime error')

    def illegal_argument(self):
        raise SystemExit(f'{self.path}: illegal argument')

    def no_this(self):
        self.name_does_not_exist('this')

    def index_out_of_range(self):
        raise SystemExit(f'{self.path}: index out of range')

    def visit(self, node, env):
        method_name = f'visit_{node[0]}_node'
        method = getattr(self, method_name)
        return method(node, env)

    def visit_empty_node(self, node, env):
        return Symbol('null')

    def visit_number_node(self, node, env):
        if not '.' in node[1]:
            result = np.clip(int(node[1]), -2**31, 2**31-1)
            return np.int32(result)

        return float(node[1])

    def visit_char_node(self, node, env):
        return Char(ord(node[1]))

    def visit_string_node(self, node, env):
        result = Object(node[1], global_env.get('String'))
        return result

    def visit_name_node(self, node, env):
        result = env.get(node[1])
        
        if result == None:
            self.name_does_not_exist(node[1])
        
        return result

    def visit_member_node(self, node, env):
        obj = self.visit(node[1], env)

        if not isinstance(obj, Object): 
            self.illegal_operation()

        result = obj.get(node[2])

        if result == None:
            self.member_does_not_exist(node[2])
        
        return result

    def visit_add_node(self, node, env):
        try:
            return self.visit(node[1], env) + self.visit(node[2], env)
        except TypeError:
            self.illegal_operation()
    
    def visit_subtract_node(self, node, env):
        try:
            return self.visit(node[1], env) - self.visit(node[2], env)
        except TypeError:
            self.illegal_operation()

    def visit_multiply_node(self, node, env):
        try:
            return self.visit(node[1], env) * self.visit(node[2], env)
        except TypeError:
            self.illegal_operation()

    def visit_divide_node(self, node, env):
        try:
            try:
                return self.visit(node[1], env) / self.visit(node[2], env)
            except ZeroDivisionError:
                return np.inf
        except TypeError:
            self.illegal_operation()

    def visit_lt_node(self, node, env):
        try:
            if self.visit(node[1], env) < self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_le_node(self, node, env):
        try:
            if self.visit(node[1], env) <= self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_gt_node(self, node, env):
        try:
            if self.visit(node[1], env) > self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_instanceof_node(self, node, env):
        instance = self.visit(node[1], env)

        if not isinstance(instance, Object): 
            self.illegal_operation()

        klass = self.visit(node[2], env)

        if not isinstance(klass, Object): 
            self.illegal_operation()
        
        if instance.klass == klass:
            return Symbol('true')
        else:
            return Symbol('false')


    def visit_ge_node(self, node, env):
        try:
            if self.visit(node[1], env) >= self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_eq_node(self, node, env):
        try:
            if self.visit(node[1], env) == self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_ne_node(self, node, env):
        try:
            if self.visit(node[1], env) != self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()
        
    def visit_and_node(self, node, env):
        try:
            if self.visit(node[1], env) and self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_or_node(self, node, env):
        try:
            if self.visit(node[1], env) or self.visit(node[2], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_call_node(self, node, env):
        should_return = self.should_return

        function = self.visit(node[1], env)

        if not isinstance(function, Object): 
            self.illegal_operation()

        args = []

        for arg_node in node[2]:
            args.append(self.visit(arg_node, env))

        try:
            if function.primitive_value == None:
                klass = self.visit(node[1], env)

                if not isinstance(klass, Object): 
                    self.illegal_operation()

                args = []

                for arg_node in node[2]:
                    args.append(self.visit(arg_node, env))

                obj = Object()
                obj.klass = klass
            
                if klass.has('constructor'):
                    constructor = klass.get('constructor')

                    if not (isinstance(constructor, Object) and callable(constructor.primitive_value)): 
                        self.illegal_operation()

                    constructor.primitive_value(args, obj)

                if should_return:
                    self.should_return = True

                return obj

            if node[1][0] == 'member':
                if should_return:
                    self.should_return = True

                return function.primitive_value(args, self.visit(node[1][1], env))

            if should_return:
                self.should_return = True

            return function.primitive_value(args, None)
        except IllegalArgument:
            self.illegal_argument()
        except NoThis:
            self.no_this()
        except IndexOutOfRange:
            self.index_out_of_range()

    def visit_plus_node(self, node, env):
        return self.visit(node[1], env)

    def visit_minus_node(self, node, env):
        try:
            return -self.visit(node[1], env)
        except TypeError:
            self.illegal_operation()

    def visit_not_node(self, node, env):
        try:
            if not self.visit(node[1], env):
                return Symbol('true')
            else:
                return Symbol('false')
        except TypeError:
            self.illegal_operation()

    def visit_assign_node(self, node, env): 
        if node[1][0] == 'member':   
            obj = self.visit(node[1][1], env)

            if not isinstance(obj, Object): 
                self.illegal_operation()

            name = node[1][2]

            value = self.visit(node[2], env)

            return obj.set(name, value)
        else:     
            if node[1][0] != 'name':
                self.raise_error()

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

        if condition:
            return self.visit(node[2], env)
        else:
            return Symbol('null')

    def visit_if_else_node(self, node, env):
        condition = self.visit(node[1], env)

        if condition:
            return self.visit(node[2], env)
        else:
            return self.visit(node[3], env)

    def visit_while_node(self, node, env):
        condition = self.visit(node[1], env)

        while condition:
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
        
        result = Object(function, global_env.get('Function'))
    
        return result

    def visit_function_node(self, node, env):
        def function(args, this):
            function_env = Env(parent=env)

            if this != None:
                function_env.set('this', this)

            for i in range(0, len(node[2])):
                arg = args[i] if i < len(args) else Symbol('null')
                function_env.set(node[2][i].value, arg)

            return self.visit(node[3], function_env)
        
        result = Object(function, global_env.get('Function'))
    
        return env.set(node[1], result)

    def visit_anonymous_class_node(self, node, env):
        result = Object()

        class_env = Env()
        
        block_env = Env(parent=env)

        for i in range(1, len(node[1])):
            result = self.visit(node[1][i], block_env)

        class_env.record.update(block_env.record)

        klass = Object(None, global_env.get('Class'), global_env.get('Object'))
        klass.update(class_env)

        return klass

    def visit_class_node(self, node, env):
        result = Object()

        class_env = Env()
        
        block_env = Env(parent=env)

        if len(node) == 0: 
            return Symbol('null')
        
        self.should_return = False

        for i in range(1, len(node[2])):
            result = self.visit(node[2][i], block_env)
            if self.should_return:
                return result        

        class_env.record.update(block_env.record)

        klass = Object(None, global_env.get('Class'), global_env.get('Object'))
        klass.update(class_env)

        env.set(node[1], klass)

        return klass

    def visit_anonymous_derived_class_node(self, node, env):
        base_class = self.visit(node[1], env)

        if not isinstance(base_class, Object):
            self.illegal_operation()

        result = Object()

        class_env = Env()
        
        block_env = Env(parent=env)

        if len(node) == 0: 
            return Symbol('null')
        
        self.should_return = False

        for i in range(1, len(node[2])):
            result = self.visit(node[2][i], block_env)
            if self.should_return:
                return result        

        class_env.record.update(block_env.record)

        klass = Object(None, global_env.get('Class'), base_class)
        klass.update(class_env)

        return klass

    def visit_derived_class_node(self, node, env):
        base_class = self.visit(node[2], env)

        if not isinstance(base_class, Object):
            self.illegal_operation()

        result = Object()

        class_env = Env()
        
        block_env = Env(parent=env)

        if len(node) == 0: 
            return Symbol('null')
        
        self.should_return = False

        for i in range(1, len(node[3])):
            result = self.visit(node[3][i], block_env)
            if self.should_return:
                return result        

        class_env.record.update(block_env.record)

        klass = Object(None, global_env.get('Class'), base_class)
        klass.update(class_env)

        env.set(node[1], klass)

        return klass

    def visit_return_node(self, node, env):
        if env.is_global_env:
            self.raise_error()

        self.should_return = True
        return self.visit(node[1], env)

    def visit_import_node(self, node, env):
        tmp = str(self.visit(node[1], env))
        if tmp in STANDARD_MODULES:
            path = Path(self.path).parent / Path(STANDARD_MODULES[tmp])
        else:
            path = Path(self.path).parent / Path(tmp)

        try:
            text = open(path, 'r').read()
        except FileNotFoundError:
            self.raise_error()

        lexer = Lexer(path, text)
        tokens = lexer.get_tokens()

        parser = Parser(path, tokens)
        tree = parser.parse()

        interpreter = Interpreter(path)
        self.visit(tree, env)

        return Symbol('null')

    def visit_statements_node(self, node, env):
        if len(node) == 0: 
            return Symbol('null')
        
        for i in range(1, len(node) - 1):
            self.visit(node[i], env)      

        return self.visit(node[-1], env)