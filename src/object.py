import textwrap
import uuid
from src.env import Env
from src.symbol import Symbol

DEFAULT_INDENT = 2
DEFAULT_MAX_DEPTH = 6
DEFAULT_PRUNED_VALUE = '...'

class Object:
    def __init__(self, primitive_value=None, klass=None, base=None):
        self.primitive_value = primitive_value
        self.record = {}
        self.klass = klass
        self.base = base
        self.uuid = f'{uuid.uuid4()}'

    def update(self, env):
        self.record.update(env.record)

    def get(self, name):
        result = self.record.get(name)

        if result is not None:
            return result

        if self.klass is not None:
            result = self.klass.get(name)

            if result is not None:
                return result

        if self.base is not None:
            result = self.base.get(name)

            if result is not None:
                return result
    
    def set(self, name, value):
        self.record[name] = value

        return value
    
    def has(self, name):            
        result = self.record.get(name) is not None
        if result: return result
    
        if self.klass is not None:
            return self.klass.has(name)
 
        if self.base is not None:
            return self.base.has(name)

        return False

    def can(self, method):
        return self.has(method) and isinstance(self.get(method), Object) and callable(self.get(method).primitive_value)

    def __eq__(self, other):
        # print(self.primitive_value, self.can('eq'))
        if isinstance(other, Object) and self.uuid == other.uuid:
            return Symbol('true')
        else:
            return Symbol('false')

    def __ne__(self, other):
        if isinstance(other, Object) and self.uuid == other.uuid:
            return Symbol('false')
        else:
            return Symbol('true')

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