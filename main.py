#!/usr/bin/env python

import sys
from src.lexer import Lexer
from src.parser import Parser
from src.interpreter import Interpreter
from src.global_env import global_env

if len(sys.argv) >= 1:
    path = sys.argv[1]
    text = open(path, 'r').read()
      
    lexer = Lexer(path, text)
    tokens = lexer.get_tokens()

    parser = Parser(path, tokens)
    tree = parser.parse()

    interpreter = Interpreter(path)
    result = interpreter.visit(tree, global_env)

    print('result: ')
    print(result)