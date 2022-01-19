package com.nirvanaself.pluto;

import java.util.List;
import java.util.ArrayList;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Pluto {
    public static void main(String[] args) {
        if(args.length == 0) {
            System.err.println("usage: java Pluto [filename]");
            System.exit(1);
        }

        String filename = args[0];
        boolean perfMode = true;

        try {
            File f = new File(filename);
            
            Scanner scan = new Scanner(f);
            scan.useDelimiter("\\Z");  

            String text = scan.next(); 
            scan.close();

            // performance mode
            if(perfMode) {
                long t1 = System.currentTimeMillis();

                Lexer lexer = new Lexer(filename, text);
                List<Token> tokens = lexer.getTokens();

                Parser parser = new Parser(filename, tokens);
                Node tree = parser.parse();

                Env globalEnv = new Env();

                Interpreter interpreter = new Interpreter(filename);   

                interpreter.visit(tree, globalEnv);

                long t2 = System.currentTimeMillis();

                System.out.println(t2 - t1);               
            } else {
                Lexer lexer = new Lexer(filename, text);
                List<Token> tokens = lexer.getTokens();

                Parser parser = new Parser(filename, tokens);
                Node tree = parser.parse();

                Env globalEnv = new Env();

                Interpreter interpreter = new Interpreter(filename);
                            
                System.out.println(interpreter.visit(tree, globalEnv));
            }
        } catch(FileNotFoundException e) {
            System.err.println("file not found: "+filename);
            System.exit(1);
        }
    }
}