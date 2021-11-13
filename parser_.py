    from tokens import TokenType
    from lexer import Lexer

    class Parser:
    def __init__(self, path, tokens):
        self.path = path
        self.tokens = iter(tokens)
        self.advance()

    def error(self):
        raise SystemExit(f'{self.path}: syntax error')

    def advance(self):
        self.current_token = next(self.tokens)
        
    def parse(self):
        if self.current_token.type == TokenType.EOF:
            return ('empty', )
        
    def expr(self):
        return self.additive_expr()
