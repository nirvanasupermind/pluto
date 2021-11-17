from src.symbol import Symbol

def is_true(v):
    if isinstance(v, Symbol):
        return v.symbol != 'false' and v.symbol != 'null'
    
    return True