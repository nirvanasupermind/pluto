package com.github.pluto;

import java.util.List;
import java.util.ArrayList;

class Lexer {
    private static final String WHITESPACE = " \n\t";
    private static final String DIGITS = "0123456789";

    private String filename;
    private String text;
    private int index = 0;
    private int line = 1;

    public Lexer(String filename, String text) {
        this.filename = filename;
        this.text = text + '\0';
    }

    public void advance() {
        index++;
        if(current() == '\n')
            line++;
    }

    public char current() {
        return text.charAt(index);
    }

    public List<Token> getTokens() {
        List<Token> tokens = new ArrayList<>();

        while(current() != '\0') {
            if(WHITESPACE.indexOf(current()) != -1) {
                advance();
            } else if(DIGITS.indexOf(current()) != -1) {
                tokens.add(getNumber());
            } else if(current() == '+') {
                tokens.add(new Token(line, TokenType.PLUS));
                advance();
            } else if(current() == '-') {
                tokens.add(new Token(line, TokenType.MINUS));
                advance();
            } else if(current() == '*') {
                tokens.add(new Token(line, TokenType.MULTIPLY));
                advance();
            } else if(current() == '/') {
                tokens.add(new Token(line, TokenType.DIVIDE));
                advance();
            } else if(current() == '%') {
                tokens.add(new Token(line, TokenType.MOD));
                advance();
            } else if(current() == '(') {
                tokens.add(new Token(line, TokenType.LPAREN));
                advance();
            } else if(current() == ')') {
                tokens.add(new Token(line, TokenType.RPAREN));
                advance();
            } else {
                Errors.illegalCharacter(filename, line, current());
            }
        }

        tokens.add(new Token(line, TokenType.EOF));

        return tokens;
    }

    public Token getNumber() {
        String val = "";
        int dotCount = 0;

        while((DIGITS + '.').indexOf(current()) != -1 && current() != '\0') {
            if(current() == '.')
                if(++dotCount >= 2) 
                    break;
            
            val += current();
            advance();
        }

        if(dotCount == 1)
            return new Token(line, TokenType.DOUBLE, Double.parseDouble(val));
        
        return new Token(line, TokenType.INT, Integer.parseInt(val));
    }
}