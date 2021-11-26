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
        if self.can('plus'):
            return self.get('add').primitive_value([other], self)
        else:
            raise TypeError()

    def __sub__(self, other):
        if self.can('minus'):
            return self.get('sub').primitive_value([other], self)
        else:
            raise TypeError()

    def __mul__(self, other):
        if self.can('mul'):
            return self.get('mul').primitive_value([other], self)
        else:
            raise TypeError()

    def __truediv__(self, other):
        if self.can('div'):
            return self.get('div').primitive_value([other], self)
        else:
            raise TypeError()

    def __lt__(self, other):
        if self.can('lt'):
            return self.get('lt').primitive_value([other], self)
        else:
            raise TypeError()

    def __le__(self, other):
        if self.can('le'):
            return self.get('le').primitive_value([other], self)
        else:
            raise TypeError()

    def __eq__(self, other):
        if self.can('eq'):
            return self.get('eq').primitive_value([other], self)
        else:
            if isinstance(other, Object) and self.uuid == other.uuid:
                return Symbol('true')
            else:
                return Symbol('false')

    def __ne__(self, other):
        if self.can('ne'):
            return self.get('ne').primitive_value([other], self)
        else:
            if isinstance(other, Object) and self.uuid == other.uuid:
                return Symbol('false')
            else:
                return Symbol('true')

    def __gt__(self, other):
        if self.can('gt'):
            return self.get('gt').primitive_value([other], self)
        else:
            raise TypeError()

    def __ge__(self, other):
        if self.can('ge'):
            return self.get('ge').primitive_value([other], self)
        else:
            raise TypeError()

    def __neg__(self):
        if self.can('neg'):
            return self.get('neg').primitive_value([], self)
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