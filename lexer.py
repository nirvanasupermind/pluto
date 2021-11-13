from tokens import TokenType, Token

WHITESPACE = ' \n\t'
DIGITS = '0123456789'

class Lexer:
    def __init__(self, path, text):
        self.path = path
        self.text = iter(text + '\0')
        self.advance()
    
    def error(self):
        raise SystemExit(f'{self.path}: lexical error')

    def advance(self):
        self.current_char = next(self.text)
    
    def get_tokens(self):
        tokens = []

        while self.current_char != '\0':
            if self.current_char in WHITESPACE:
                self.advance();
            elif self.current_char in (DIGITS + '.'):
                tokens.append(self.get_number())
            elif self.current_char == '+':
                self.advance()
                tokens.append(Token(TokenType.PLUS))
            elif self.current_char == '.':
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
            else:
                self.error()

        return tokens

    def get_number(self):
        value = ''
        dot_count = 0

        while self.current_char in DIGITS + '.':
            if(self.current_char == '.'):
                dot_count += 1
                if dot_count > 1: break
            
            value += self.current_char
            self.advance()

        return Token('NUMBER', value)

class Lexer:
    def __init__(self, path, text):
        self.path = path
        self.text = iter(text + '\0')
        self.advance()
    
    def error(self):
        raise SystemExit(f'{self.path}: lexical error')

    def advance(self):
        self.current_char = next(self.text)
    
    def get_tokens(self):
        tokens = []

        while self.current_char != '\0':
            if self.current_char in WHITESPACE:
                self.advance();
            elif self.current_char in (DIGITS + '.'):
                tokens.append(self.get_number())
            elif self.current_char == '+':
                self.advance()
                tokens.append(Token(TokenType.PLUS))
            elif self.current_char == '.':
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
            else:
                self.error()

        tokens.append(Token(TokenType.EOF))

        return tokens

    def get_number(self):
        value = ''
        dot_count = 0

        while self.current_char in DIGITS + '.':
            if(self.current_char == '.'):
                dot_count += 1
                if dot_count > 1: break
            
            value += self.current_char
            self.advance()

        return Token('NUMBER', value)