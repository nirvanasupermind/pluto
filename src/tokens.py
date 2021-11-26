from enum import Enum, auto

class TokenType(Enum):
    NUMBER = auto()
    CHAR = auto()
    STRING = auto()
    NAME = auto()
    KEYWORD = auto()
    PLUS = auto()
    MINUS = auto()
    MULTIPLY = auto()
    DIVIDE = auto()
    LT = auto()
    LE = auto()
    GT = auto()
    GE = auto()
    EQ = auto()
    EE = auto()
    NE = auto()
    AND = auto()
    OR = auto()
    NOT = auto()
    DOT = auto()
    COMMA = auto()
    LPAREN = auto()
    RPAREN = auto()
    LCURLY = auto()
    RCURLY = auto()
    EOF = auto()

class Token:
    def __init__(self, type, value=None):
        self.type = type
        self.value = value

    def matches(self, type, value):
        return self.type == type and self.value == value

    def __repr__(self):
        return self.type.name + (f':{self.value}' if self.value != None else '')
