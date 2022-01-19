package com.nirvanaself.pluto;

public class Value {
    public static final Value NIL = new Value(ValueType.NIL);

    public ValueType type;
    public byte byteVal = (byte)0;
    public int intVal = 0;
    public double doubleVal = 0.0;
    public boolean boolVal = true;

    //Don't let anyone crete another nil
    private Value(ValueType type) {
        this.type = type;
    }

    public Value(ValueType type, byte byteVal) {
        this.type = type;
        this.byteVal = byteVal;
    }

    public Value(ValueType type, int intVal) {
        this.type = type;
        this.intVal = intVal;
    } 

    public Value(ValueType type, double doubleVal) {
        this.type = type;
        this.doubleVal = doubleVal;
    }

    public Value(ValueType type, boolean boolVal) {
        this.type = type;
        this.boolVal = boolVal;
    }

    public String toString() {
        String result = "";

        switch(this.type) {
            case NIL:
                result = "nil";
                break;
            case BYTE:
                result = String.valueOf(byteVal);
                break;
            case INT:
                result = String.valueOf(intVal);
                break;
            case DOUBLE:
                result = String.valueOf(doubleVal);
                break;
        }

        return result;
    }
}