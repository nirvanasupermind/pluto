package com.nirvanaself.pluto;

public class Token {
    public int line = 0;
    public TokenType type;
    public byte byteVal = (byte)0;
    public int intVal = 0;
    public double doubleVal = 0.0;
    public String id;

    public Token(int line, TokenType type) {
        this.line = line;
        this.type = type;
    }

    public Token(int line, TokenType type, byte byteVal) {
        this.line = line;
        this.type = type;
        this.byteVal = byteVal;
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

    public Token(int line, TokenType type, String id) {
        this.line = line;
        this.type = type;
        this.id = id;
    }
    
    @Override
    public String toString() {
        if(type == TokenType.BYTE)
            return String.format("%s:%s", type, byteVal);

        if(type == TokenType.INT)
            return String.format("%s:%s", type, intVal);

        if(type == TokenType.DOUBLE)
            return String.format("%s:%s", type, doubleVal);

        return type.toString();
    }
}