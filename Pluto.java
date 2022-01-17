package com.github.pluto;

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

        try {
            File f = new File(filename);
            
            Scanner scan = new Scanner(f);
            scan.useDelimiter("\\Z");  

            String text = scan.next(); 
            scan.close();

            Lexer lexer = new Lexer(filename, text);
            List<Token> tokens = lexer.getTokens();

            Parser parser = new Parser(filename, tokens);
            Node tree = parser.parse();

            System.out.println(tree);
        } catch(FileNotFoundException e) {
            System.err.println("file not found: "+filename);
            System.exit(1);
        }
    }
}