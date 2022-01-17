package com.nirvanaself.pluto;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

public class Lexer {
    private static final String WHITESPACE = " \n\t";
    private static final String DIGITS = "0123456789";
    private static final Map<Character, Character> ESCAPES = new HashMap<>();

    private String filename;
    private String text;
    private int index = 0;
    private int line = 1;

    public Lexer(String filename, String text) {
        this.filename = filename;
        this.text = text + '\0';
        addEscapes();
    }

    private void addEscapes() {
        ESCAPES.put('n', '\n');
        ESCAPES.put('t', '\t');
    }

    private void advance() {
        index++;
        if(current() == '\n')
            line++;
    }

    private char current() {
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
            } else if(current() == '\'') {
                tokens.add(getChar());
            } else {
                Errors.illegalCharacter(filename, line, current());
            }
        }

        tokens.add(new Token(line, TokenType.EOF));

        return tokens;
    }

    private Token getNumber() {
        String val = "";
        int dotCount = 0;

        while((DIGITS + '.').indexOf(current()) != -1 && current() != '\0') {
            if(current() == '.') {
                if(++dotCount >= 2) {
                    break;
                }
            }
            
            val += current();
            advance();
        }

        if(dotCount == 1)
            return new Token(line, TokenType.DOUBLE, Double.parseDouble(val));
        
        return new Token(line, TokenType.INT, Integer.parseInt(val));
    }

    private Token getChar() {
        advance();

        char val = '\0';
        
        if(current() == '\'') {
            Errors.emptyCharacterLiteral(filename, line);
        } else if(current() == '\\') {
            advance();
            val = ESCAPES.getOrDefault(current(), current());
        } else {
            val = current();
        }

        advance();

        if(current() != '\'') {
            Errors.unclosedCharacterLiteral(filename, line);
        } 

        advance();
        
        return new Token(line, TokenType.CHAR, val);
    }
}