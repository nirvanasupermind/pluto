package com.github.pluto;

class Token {
    public int line = 0;
    public TokenType type;
    public int intVal = 0;
    public double doubleVal = 0.0;

    public Token(int line, TokenType type) {
        this.line = line;
        this.type = type;
    }

    public Token(int line, TokenType type, int intVal) {
        this.line = line;
        this.type = type;
        this.intVal = intVal;
    }

    public Token(int line, TokenType type, double doubleVal) {
        this.line = line;
        this.type = type;
        this.doubleVal = doubleVal;
    }
    
    @Override
    public String toString() {
        if(type == TokenType.INT)
            return String.format("%s:%s", type, intVal);

        if(type == TokenType.DOUBLE)
            return String.format("%s:%s", type, doubleVal);

        return String.format("%s", type);
    }
}