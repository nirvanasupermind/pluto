class Symbol:
    def __init__(self, symbol):
        self.symbol = symbol

    def __eq__(self, other):
        return isinstance(other, Symbol) and self.symbol == other.symbol

    def __ne__(self, other):
        return not (self == other)

    def __bool__(self):
        return self.symbol != 'false' and self.symbol != 'null'

    def __repr__(self):
        return f'{self.symbol}'