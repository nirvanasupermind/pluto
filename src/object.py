import uuid
from src.env import Env

class Object:
    def __init__(self, primitive_value=None):
        self.primitive_value = primitive_value
        self.env = Env()
        self.id = uuid.uuid4().hex
    
    def __repr__(self):
        if self.primitive_value != None and not callable(self.primitive_value): 
            return f'{self.primitive_value}'
            
        return self.id