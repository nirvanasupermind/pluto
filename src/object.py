import numpy as np
import textwrap
import uuid
from src.env import Env
from src.symbol import Symbol

def java_string_hashcode(s):
    """Mimic Java's hashCode in python 2"""
    # try:
    #     s = unicode(s)
    # except:
    #     try:
    #         s = unicode(s.decode('utf8'))
    #     except:
    #         raise Exception("Please enter a unicode type string or utf8 bytestring.")
    h = 0
    for c in s:
        h = int((((31 * h + ord(c)) ^ 0x80000000) & 0xFFFFFFFF) - 0x80000000)
    return h

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
        if isinstance(other, Object) and self.hashcode() == other.hashcode():
            return Symbol('true')
        else:
            return Symbol('false')

    def __ne__(self, other):
        if isinstance(other, Object) and self.uuid == other.uuid:
            return Symbol('false')
        else:
            return Symbol('true')

    def hashcode(self):
        if self.can('hashCode') and self.base != None:
            result = self.get('hashCode').primitive_value([], self)
            return np.int32(result)
        
        return java_string_hashcode(self.uuid)

    def __repr__(self):        
        if self.can('toString') and self.base != None:
            result = self.get('toString').primitive_value([], self)
            if isinstance(result, Object): return f'{result.primitive_value}'
            return f'{result}'
        
        return '0x%02X' % (self.hashcode() & 0xffffffff)

        # old yaml-like thing
            
        # if depth > DEFAULT_MAX_DEPTH:
        #     return DEFAULT_PRUNED_VALUE

        # result = ''
        # for key in self.record:
        #     value = self.record[key]

        #     if isinstance(value, Object) and not value.can('toString'):
        #         result += (f'{key}: \n{textwrap.indent(value.__repr__(depth+1), " " * DEFAULT_INDENT)}\n')        
        #     else:
        #         result += f'{key}: {value}\n'
        
        # return result[0:-1]