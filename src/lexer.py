import string
from src.tokens import Token, TokenType

WHITESPACE = ' \t\r\n'
DIGITS = '0123456789'
LETTERS = '_' + string.ascii_letters
KEYWORDS = [
    'var'
]

class Lexer:
    def __init__(self, path, text):
        self.path = path
        self.text = iter(text)
        self.advance()
    
    def raise_error(self):
        raise SystemExit(f'{self.path}: lexical error')
    
    def advance(self):
        try:
            self.current_char = next(self.text)
        except StopIteration:
            self.current_char = None

    def get_tokens(self):
        tokens = []
        
        while self.current_char != None:
            if self.current_char in WHITESPACE:
                self.advance()
            elif self.current_char in (DIGITS + '.'):
                tokens.append(self.get_number())
            elif self.current_char in (LETTERS + DIGITS):
                tokens.append(self.get_name())
            elif self.current_char == '+':
                self.advance()
                tokens.append(Token(TokenType.PLUS))
            elif self.current_char == '-':
                self.advance()
                tokens.append(Token(TokenType.MINUS))
            elif self.current_char == '*':
                self.advance()
                tokens.append(Token(TokenType.MULTIPLY))
            elif self.current_char == '/':
                self.advance()
                tokens.append(Token(TokenType.DIVIDE))
            elif self.current_char == '(':
                self.advance()
                tokens.append(Token(TokenType.LPAREN))
            elif self.current_char == ')':
                self.advance()
                tokens.append(Token(TokenType.RPAREN))
            elif self.current_char == '{':
                self.advance()
                tokens.append(Token(TokenType.LCURLY))
            elif self.current_char == '}':
                self.advance()
                tokens.append(Token(TokenType.RCURLY))
            elif self.current_char == '=':
                self.advance()
                tokens.append(Token(TokenType.EQ))
            elif self.current_char == ';':
                self.advance()
                tokens.append(Token(TokenType.SEMICOLON))
            else:
                self.raise_error()

        tokens.append(Token(TokenType.EOF))
        
        return tokens
    
    def get_number(self):
        value = self.current_char
        decimal_point_count = 0

        self.advance()

        while self.current_char != None and self.current_char in (DIGITS + '.'):
            if self.current_char == '.':
                decimal_point_count += 1
                if decimal_point_count > 1:
                    break
            
            value += self.current_char
            self.advance()

        if value == '.': 
            return Token(TokenType.DOT)
    
        return Token(TokenType.NUMBER, float(value))

    def get_name(self):
        value = self.current_char

        self.advance()

        while self.current_char != None and self.current_char in LETTERS:            
            value += self.current_char
            self.advance()

        if value == '.': 
            return Token(TokenType.DOT)

        if value in KEYWORDS:
            return Token(TokenType.KEYWORD, value)     
               
        return Token(TokenType.NAME, value)