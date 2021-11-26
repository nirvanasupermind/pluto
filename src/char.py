import numpy as np

class Char(np.uint16):
    def __repr__(self):
        return f'{chr(self)}'

    def __str__(self):
        return f'{chr(self)}'