class Env:
    def __init__(self, parent=None, is_global_env=False):
        self.record = {}
        self.parent = parent
        self.is_global_env = is_global_env
    
    def get(self, name):
        result = self.record.get(name)

        if result == None and self.parent != None:
            result = self.parent.get(name)

        return result
    
    def set(self, name, value):
        self.record[name] = value

        return value
    
    def has(self, name):
        return self.get(name) != None