from src.tokens import TokenType

class Parser:
    def __init__(self, path, tokens):
        self.path = path
        self.tokens = iter(tokens)
        self.advance()

    def raise_error(self):
        raise SystemExit(f'{self.path}: syntax error')

    def advance(self):
        try:
            self.current_token = next(self.tokens)
        except StopIteration:
            self.current_token = None

    def parse(self):
        if self.current_token.type == TokenType.EOF:
            return ('empty',)

        result = self.statements()

        if self.current_token.type != TokenType.EOF:
            self.raise_error()

        return result

    def statements(self):
        statements = [self.expr()]
    
        while self.current_token.type != TokenType.EOF:
            # self.advance()
            statements.append(self.expr())        

        return ('statements', *statements)

    def expr(self):
        result = self.assignment_expr()

        while self.current_token.type != TokenType.EOF and self.current_token.type == TokenType.SEMICOLON:
            self.advance()

        return result

    def assignment_expr(self):
        result = self.additive_expr()

        if self.current_token.type == TokenType.EQ:
            self.advance()
            return ('assign', result, self.expr())
        else:
            return result
   
    def additive_expr(self):
        result = self.multiplicative_expr()

        while self.current_token.type != TokenType.EOF and self.current_token.type in (TokenType.PLUS, TokenType.MINUS):
            if self.current_token.type == TokenType.PLUS:
                self.advance()
                result = ('add', result, self.multiplicative_expr())
            elif self.current_token.type == TokenType.MINUS:
                self.advance()
                result = ('subtract', result, self.multiplicative_expr())

        return result

    def multiplicative_expr(self):
        result = self.unary_expr()

        while self.current_token != None and self.current_token.type in (TokenType.MULTIPLY, TokenType.DIVIDE):
            if self.current_token.type == TokenType.MULTIPLY:
                self.advance()
                result = ('multiply', result, self.unary_expr())
            elif self.current_token.type == TokenType.DIVIDE:
                self.advance()
                result = ('divide', result, self.unary_expr())
                
        return result

    def unary_expr(self):
        token = self.current_token

        if token.type == TokenType.PLUS:
            self.advance()
            return ('plus', self.unary_expr())
        
        elif token.type == TokenType.MINUS:
            self.advance()
            return ('minus', self.unary_expr())

        else:
            return self.paren_expr()

    def paren_expr(self):
        
        if self.current_token.type == TokenType.LPAREN:
            self.advance()
            result = self.expr()

            if self.current_token.type != TokenType.RPAREN:
                self.raise_error()
            
            self.advance()
            return result
        else:
            return self.leaf_expr()
   
    def leaf_expr(self):
        token = self.current_token

        if token.type == TokenType.NUMBER:
            self.advance()
            return ('number', token.value)

        elif token.type == TokenType.NAME:
            self.advance()
            return ('name', token.value)

        else:
            self.raise_error()