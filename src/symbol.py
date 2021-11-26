class Symbol:
    def __init__(self, symbol):
        super().__init__()
        self.symbol = symbol


    def __bool__(self):
        return self.symbol != 'false' and self.symbol != 'null'

    def __repr__(self):
        return f'{self.symbol}'