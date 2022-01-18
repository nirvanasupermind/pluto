package com.nirvanaself.pluto;

public class Errors {
    public static void illegalCharacter(String filename, int line, char chr) {
        throw new PlutoException(String.format("%s:%s: illegal character '%s'",  filename, line, chr));
    }

    public static void invalidSyntax(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: invalid syntax",  filename, line));
    }

    public static void badOperandType(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: bad operand type", filename, line));
    }

    public static void divideByZero(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: / by zero",  filename, line));
    }

    public static void modByZero(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: % by zero",  filename, line));
    }

    public static void invaildLeftHandSide(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: invalid left-hand side in assignment", filename, line));
    }

    public static void variableIsNotDefined(String filename, int line, String name) {
        throw new PlutoException(String.format("%s:%s: variable '%s' is not defined",  filename, line, name));
    }

    public static void variableIsAlreadyDefined(String filename, int line, String name) {
        throw new PlutoException(String.format("%s:%s: variable '%s' is already defined",  filename, line, name));
    }
}