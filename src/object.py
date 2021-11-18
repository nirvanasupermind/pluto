import uuid
from src.env import Env

class Object:
    def __init__(self, primitive_value=None):
        self.primitive_value = primitive_value
        self.env = Env()
        self.uuid = f'{uuid.uuid4()}'

    def __repr__(self):
        # if self.primitive_value != None and not callable(self.primitive_value): 
        #     return f'{self.primitive_value}'
        
        if self.env.has('toString') and isinstance(self.env.get('toString'), Object) and callable(self.env.get('toString').primitive_value):
            result = self.env.get("toString").primitive_value([], self)
            if isinstance(result, Object): return f'{result.primitive_value}'
            return f'{result}'
            
        return self.uuid