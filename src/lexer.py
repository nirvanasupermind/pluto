from src.tokens import Token, TokenType

WHITESPACE = " \n\t"
DIGITS = "0123456789"

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
            elif self.current_char == ';':
                self.advance()
                tokens.append(Token(TokenType.SEMICOLON))
            else:
                self.raise_error()

        tokens.append(Token(TokenType.EOF))
        
        return tokens
    
    def get_number(self):
        value = ''
        decimal_point_count = 0

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