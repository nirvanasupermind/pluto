import numpy as np

class Char(np.int32):
    def __repr__(self):
        return f'{chr(self)}'

    def __str__(self):
        return f'{chr(self)}'