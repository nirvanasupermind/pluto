package com.nirvanaself.pluto;

public class Value {
    public ValueType type;
    public int intVal = 0;
    public double doubleVal = 0.0;
    
    public Value(ValueType type) {
        this.type = type;
    }

    public Value(ValueType type, int intVal) {
        this.type = type;
        this.intVal = intVal;
    } 

    public Value(ValueType type, double doubleVal) {
        this.type = type;
        this.doubleVal = doubleVal;
    }

    public Value(ValueType type, char chr) {
        this.type = type;
        this.intVal = (int)chr;
    }

    public String toString() {
        String result = "";

        switch(this.type) {
            case NIL:
                result = "nil";
                break;
            case INT:
                result = String.valueOf(intVal);
                break;
            case DOUBLE:
                result = String.valueOf(doubleVal);
                break;
            case CHAR:
                result = String.valueOf((char)intVal);
                break;
        }

        return result;
    }
}