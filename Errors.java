package com.github.pluto;

class Errors {
    static void illegalCharacter(String filename, int line, char chr) {
        System.err.println(String.format("%s:%s: illegal character: %s",  filename, line, chr));
        System.exit(1);
    }

    static void invalidSyntax(String filename, int line) {
        System.err.println(String.format("%s:%s: invalid syntax",  filename, line));
        System.exit(1);
    }

    static void unboundVariable(String filename, int line, String name) {
        System.err.println(String.format("%s:%s: unbound variable: %s",  filename, line, name));
        System.exit(1);
    }
}