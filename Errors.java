package com.nirvanaself.pluto;

public class Errors {
    public static void illegalCharacter(String filename, int line, char chr) {
        throw new PlutoException(String.format("%s:%s: illegal character: %s",  filename, line, chr));
    }

    public static void emptyCharacterLiteral(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: empty character literal", filename, line));
    }

    public static void unclosedCharacterLiteral(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: unclosed character literal", filename, line));
    }

    public static void invalidSyntax(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: invalid syntax",  filename, line));
    }

    public static void badOperandType(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: bad operand type", filename, line));
    }

    public static void integerDivisionByZero(String filename, int line) {
        throw new PlutoException(String.format("%s:%s: integer division by zero",  filename, line));
    }

    public static void unboundVariable(String filename, int line, String name) {
        throw new PlutoException(String.format("%s:%s: unbound variable: %s",  filename, line, name));
    }
}