import string
from src.tokens import Token, TokenType

WHITESPACE = ' \t\r\n'
DIGITS = '0123456789'
LETTERS = '_' + string.ascii_letters
KEYWORDS = [
    'if',
    'else',
    'while',
    'function',
    'return',
    'class',
    'enum',
    'extends'
]

ESCAPE_CHARACTERS = {
    'n': '\n',
    't': '\t',
    'r': '\r'
}

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
            elif self.current_char == "'":
                tokens.append(self.get_char())
            elif self.current_char == '"':
                tokens.append(self.get_string())
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
            elif self.current_char == '<':
                self.advance()
                if self.current_char == '=':
                    self.advance()
                    tokens.append(Token(TokenType.LE))
                else:
                    tokens.append(Token(TokenType.LT)) 
            elif self.current_char == '>':
                self.advance()
                if self.current_char == '=':
                    self.advance()
                    tokens.append(Token(TokenType.GE))
                else:
                    tokens.append(Token(TokenType.GT)) 
            elif self.current_char == '=':
                self.advance()
                if self.current_char == '=':
                    self.advance()
                    tokens.append(Token(TokenType.EE))
                else:
                    tokens.append(Token(TokenType.EQ))
            elif self.current_char == '!':
                self.advance()
                if self.current_char == '=':
                    self.advance()
                    tokens.append(Token(TokenType.NE))
                else:
                    tokens.append(Token(TokenType.NOT))
            elif self.current_char == '&':
                self.advance()
                if self.current_char == '&':
                    self.advance()
                    tokens.append(Token(TokenType.AND))
                else:
                    self.raise_error()
            elif self.current_char == '|':
                self.advance()
                if self.current_char == '|':
                    self.advance()
                    tokens.append(Token(TokenType.OR))
                else:
                    self.raise_error()
            elif self.current_char == ',':
                self.advance()
                tokens.append(Token(TokenType.COMMA))
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
    
        return Token(TokenType.NUMBER, value)
    
    def get_char(self):
        value = ''
        escape_character = False
        
        self.advance()

        while self.current_char != "'":
            if self.current_char == None:
                self.raise_error()

            if escape_character:
                value += ESCAPE_CHARACTERS.get(self.current_char, self.current_char)
                escape_character = False
            else:
                if self.current_char == '\\':
                    escape_character = True
                else:
                    value += self.current_char
                
            self.advance()
        
        self.advance()

        if len(value) != 1:
            self.raise_error()

        return Token(TokenType.CHAR, value)

    def get_string(self):
        value = ''
        escape_character = False
        
        self.advance()

        while self.current_char != '"':
            if self.current_char == None:
                self.raise_error()
                escape_character = False

            if escape_character:
                value += ESCAPE_CHARACTERS.get(self.current_char, self.current_char)
            else:
                if self.current_char == '\\':
                    escape_character = True
                else:
                    value += self.current_char
                

            self.advance()
            
        self.advance()
        return Token(TokenType.STRING, value)

    def get_name(self):
        value = self.current_char

        self.advance()

        while self.current_char != None and self.current_char in (LETTERS + DIGITS):            
            value += self.current_char
            self.advance()


        if value in KEYWORDS:
            return Token(TokenType.KEYWORD, value)     
               
        return Token(TokenType.NAME, value)