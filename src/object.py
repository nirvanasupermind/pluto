import uuid
from src.env import Env

class Object:
    def __init__(self, primitive_value=None):
        self.primitive_value = primitive_value
        self.env = Env()
        self.uuid = f'{uuid.uuid4()}'

    def can(self, method):
        return self.env.has(method) and isinstance(self.env.get(method), Object) and callable(self.env.get(method).primitive_value)

    def __add__(self, other):
        if self.can('add'):
            return self.env.get('add').primitive_value([other], self)
        else:
            raise TypeError()

    def __sub__(self, other):
        if self.can('subtract'):
            return self.env.get('subtract').primitive_value([other], self)
        else:
            raise TypeError()

    def __mul__(self, other):
        if self.can('multiply'):
            return self.env.get('multiply').primitive_value([other], self)
        else:
            raise TypeError()

    def __truediv__(self, other):
        if self.can('divide'):
            return self.env.get('divide').primitive_value([other], self)
        else:
            raise TypeError()

    def __neg__(self):
        if self.can('negate'):
            return self.env.get('negate').primitive_value([], self)
        else:
            raise TypeError()

    def __repr__(self):
        # if self.primitive_value != None and not callable(self.primitive_value): 
        #     return f'{self.primitive_value}'
        
        if self.can('toString'):
            result = self.env.get("toString").primitive_value([], self)
            if isinstance(result, Object): return f'{result.primitive_value}'
            return f'{result}'
            
        return self.uuid