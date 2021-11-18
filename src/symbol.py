class Symbol:
    def __init__(self, symbol):
        super().__init__()
        self.symbol = symbol

    def __repr__(self):
        return f'{self.symbol}'