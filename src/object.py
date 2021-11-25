import textwrap
import uuid
from src.env import Env

DEFAULT_INDENT = 2
DEFAULT_MAX_DEPTH = 6
DEFAULT_PRUNED_VALUE = '...'

class Object:
    def __init__(self, primitive_value=None):
        self.primitive_value = primitive_value
        self.record = {}
        self.klass = None
        self.base = None
        self.uuid = f'{uuid.uuid4()}'

    def update(self, env):
        self.record.update(env.record)

    def get(self, name):
        result = self.record.get(name)

        if result != None:
            return result

        if self.klass != None:
            result = self.klass.get(name)

            if result != None:
                return result

        if self.base != None:
            result = self.base.get(name)

            if result != None:
                return result
    
    def set(self, name, value):
        self.record[name] = value

        return value
    
    def has(self, name):
        return self.get(name) != None

    def can(self, method):
        return self.has(method) and isinstance(self.get(method), Object) and callable(self.get(method).primitive_value)

    def __add__(self, other):
        if self.can('add'):
            return self.get('add').primitive_value([other], self)
        else:
            raise TypeError()

    def __sub__(self, other):
        if self.can('subtract'):
            return self.get('subtract').primitive_value([other], self)
        else:
            raise TypeError()

    def __mul__(self, other):
        if self.can('multiply'):
            return self.get('multiply').primitive_value([other], self)
        else:
            raise TypeError()

    def __truediv__(self, other):
        if self.can('divide'):
            return self.get('divide').primitive_value([other], self)
        else:
            raise TypeError()

    def __neg__(self):
        if self.can('negate'):
            return self.get('negate').primitive_value([], self)
        else:
            raise TypeError()

    def __repr__(self, depth=0):        
        if self.can('toString'):
            result = self.get('toString').primitive_value([], self)
            if isinstance(result, Object): return f'{result.primitive_value}'
            return f'{result}'
            
        if depth > DEFAULT_MAX_DEPTH:
            return DEFAULT_PRUNED_VALUE

        result = ''
        for key in self.record:
            value = self.record[key]

            if isinstance(value, Object) and not value.can('toString'):
                result += (f'{key}: \n{textwrap.indent(value.__repr__(depth+1), " " * DEFAULT_INDENT)}\n')        
            else:
                result += f'{key}: {value}\n'
        
        return result[0:-1]