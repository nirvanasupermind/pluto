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
        return self.statements()

    def statements(self, stop_at=TokenType.EOF):
        if self.current_token.type == stop_at:
            return ('empty',)

        statements = [self.expr()]
    
        while self.current_token.type != stop_at:
            statements.append(self.expr())        

        if self.current_token.type != stop_at:
            self.raise_error()

        return ('statements', *statements)

    def expr(self):
        if self.current_token.matches(TokenType.KEYWORD, 'return'):
            return self.return_expr()

        return self.assignment_expr()


    def return_expr(self):
        self.advance()

        expr = self.expr()

        return ('return', expr)

    def assignment_expr(self):
        result = self.equality_expr()

        if self.current_token.type == TokenType.EQ:
            self.advance()
            return ('assign', result, self.expr())
        else:
            return result

    def equality_expr(self):
        result = self.relational_expr()

        while self.current_token.type != TokenType.EOF and self.current_token.type in (TokenType.EE, TokenType.NE):
            if self.current_token.type == TokenType.EE:
                self.advance()
                result = ('eq', result, self.relational_expr())
            elif self.current_token.type == TokenType.NE:
                self.advance()
                result = ('ne', result, self.relational_expr())

        return result

    def relational_expr(self):
        result = self.additive_expr()

        while self.current_token.type != TokenType.EOF and self.current_token.type in (TokenType.LT, TokenType.LE, TokenType.GT, TokenType.GE):
            if self.current_token.type == TokenType.LT:
                self.advance()
                result = ('lt', result, self.additive_expr())
            elif self.current_token.type == TokenType.LE:
                self.advance()
                result = ('le', result, self.additive_expr())
            elif self.current_token.type == TokenType.GT:
                self.advance()
                result = ('gt', result, self.additive_expr())
            elif self.current_token.type == TokenType.GE:
                self.advance()
                result = ('ge', result, self.additive_expr())
            
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
            return self.call_expr()

    def call_expr(self):
        result = self.paren_expr()

        while self.current_token.type == TokenType.LPAREN or self.current_token.type == TokenType.DOT:
            if self.current_token.type == TokenType.DOT:
                self.advance()
                if self.current_token.type != TokenType.NAME:
                    self.raise_error()
                
                result = ('member', result, self.current_token.value)
                self.advance()
            else:   
                args = self.arg_list()
                result = ('call', result, args)

        return result

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

        elif token.type == TokenType.CHAR:
            self.advance()
            return ('char', token.value)

        elif token.type == TokenType.STRING:
            self.advance()
            return ('string', token.value)

        elif token.type == TokenType.NAME:
            self.advance()
            return ('name', token.value)

        elif token.type == TokenType.LCURLY:
            return self.block_expr()

        elif token.matches(TokenType.KEYWORD, 'if'):
            return self.if_expr()

        elif token.matches(TokenType.KEYWORD, 'while'):
            return self.while_expr()

        elif token.matches(TokenType.KEYWORD, 'function'):
            return self.function_expr()

        elif token.matches(TokenType.KEYWORD, 'class'):
            return self.class_expr()

        else:
            self.raise_error()

    def block_expr(self):
        if self.current_token.type != TokenType.LCURLY:
            self.raise_error()
        
        self.advance()
        
        statements = self.statements(TokenType.RCURLY)

        if self.current_token.type != TokenType.RCURLY:
            self.raise_error()
        
        self.advance()

        return ('block', statements)

    def if_expr(self):
        self.advance()

        if self.current_token.type != TokenType.LPAREN:
            self.raise_error()
        
        self.advance()

        condition = self.expr()

        if self.current_token.type != TokenType.RPAREN:
            self.raise_error()
        
        self.advance()

        if_body = self.block_expr()

        if self.current_token.matches(TokenType.KEYWORD, 'else'):
            self.advance()

            else_body = self.block_expr()
            
            return ('if_else', condition, if_body, else_body)   

        return ('if', condition, if_body)

    def while_expr(self):
        self.advance()

        if self.current_token.type != TokenType.LPAREN:
            self.raise_error()
        
        self.advance()

        condition = self.expr()

        if self.current_token.type != TokenType.RPAREN:
            self.raise_error()
        
        self.advance()

        body = self.block_expr()

        return ('while', condition, body) 

    def function_expr(self):
        self.advance()

        if self.current_token.type == TokenType.NAME:
            name = self.current_token.value

            self.advance()

            arg_name_tokens = self.arg_name_list()
            
            body = self.block_expr()

            return ('function', name, arg_name_tokens, body)

        arg_name_tokens = self.arg_name_list()
            
        body = self.block_expr()

        return ('anonymous_function', arg_name_tokens, body)

    def class_expr(self):
        self.advance()

        if self.current_token.matches(TokenType.KEYWORD, 'extends'):
            self.advance()

            base_class = self.expr()

            body = self.block_expr()

            return ('anonymous_derived_class', base_class, body) 

        if self.current_token.type == TokenType.NAME:
            name = self.current_token.value

            self.advance()

            if self.current_token.matches(TokenType.KEYWORD, 'extends'):
                self.advance()

                base_class = self.expr()

                body = self.block_expr()

                return ('derived_class', name, base_class, body) 

            body = self.block_expr()

            return ('class', name, body)

        body = self.block_expr()

        return ('anonymous_class', body)

    # utility parsers

    def arg_name_list(self):
        if self.current_token.type != TokenType.LPAREN:
            self.raise_error()
        
        self.advance()

        arg_name_tokens = []


        if self.current_token.type != TokenType.RPAREN:
            if self.current_token.type != TokenType.NAME:
                self.raise_error()

            arg_name_tokens.append(self.current_token)

            self.advance()

            if self.current_token.type != TokenType.RPAREN:
                while self.current_token.type == TokenType.COMMA:
                    self.advance()

                    if self.current_token.type != TokenType.NAME:
                        self.raise_error()
                    
                    arg_name_tokens.append(self.current_token)
                    self.advance()
                
                if self.current_token.type != TokenType.RPAREN:
                    self.raise_error()

            
        self.advance()

        return arg_name_tokens

    def arg_list(self):
        if self.current_token.type != TokenType.LPAREN:
            self.raise_error()
        
        self.advance()


        result = []


        if self.current_token.type != TokenType.RPAREN:
            result.append(self.expr())

            if self.current_token.type != TokenType.RPAREN:
                while self.current_token.type == TokenType.COMMA:
                    self.advance()                    
                    result.append(self.expr())

                if self.current_token.type != TokenType.RPAREN:
                    self.raise_error()

            
        self.advance()

        return result