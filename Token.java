package com.github.pluto;

class Token {
    private int line = 0;
    private TokenType type;
    private int intVal = 0;
    private double doubleVal = 0;

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

    public int getLine() {
        return line;
    }
    
    public TokenType getType() {
        return type;
    }

    public int getIntVal() {
        return intVal;
    }

    public double getDoubleVal() {
        return doubleVal;
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