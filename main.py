#!/usr/bin/env python3

import sys
from lexer import Lexer

if len(sys.argv) >= 2:
    path = sys.argv[1]
    text = open(path, 'r').read()

    lexer = Lexer(path, text)
    tokens = lexer.get_tokens()

    print(tokens)
