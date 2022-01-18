package com.nirvanaself.pluto;

public class Interpreter {
    private String filename;

    public Interpreter(String filename) {
        this.filename = filename;
    }

    public Value visit(Node node) {
        switch(node.type) {
            case EmptyNode:
                return new Value(ValueType.NIL);
            case ByteNode:
                return visitByteNode(node);
            case IntNode:
                return visitIntNode(node);
            case DoubleNode:
                return visitDoubleNode(node);
            case AddNode:
                return visitAddNode(node); 
            case SubtractNode:
                return visitSubtractNode(node); 
            case MultiplyNode:
                return visitMultiplyNode(node);
            case DivideNode:
                return visitDivideNode(node);
            case ModNode:
                return visitModNode(node);
            case PlusNode:
                return visitPlusNode(node);
            case MinusNode:
                return visitMinusNode(node);
            default:
                throw new PlutoException("Unknown node type");
        }
    }

    private Value visitByteNode(Node node) {
        return new Value(ValueType.BYTE, node.byteVal);
    }
    
    private Value visitIntNode(Node node) {
        return new Value(ValueType.INT, node.intVal);
    }

    private Value visitDoubleNode(Node node) {
        return new Value(ValueType.DOUBLE, node.doubleVal);       
    }


    private Value visitAddNode(Node node) {
        Value a = visit(node.nodeA);
        Value b = visit(node.nodeB);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, a.byteVal + b.byteVal);
        } else if(a.type == ValueType.BYTE && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.byteVal + b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.BYTE) {
            return new Value(ValueType.INT, a.intVal + b.byteVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.intVal + b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.intVal + b.doubleVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.BYTE) {
            return new Value(ValueType.DOUBLE, a.doubleVal + b.byteVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.INT) {
            return new Value(ValueType.DOUBLE, a.doubleVal + b.intVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.doubleVal + b.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }

    private Value visitSubtractNode(Node node) {
        Value a = visit(node.nodeA);
        Value b = visit(node.nodeB);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, a.byteVal - b.byteVal);
        } else if(a.type == ValueType.BYTE && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.byteVal - b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.BYTE) {
            return new Value(ValueType.INT, a.intVal - b.byteVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.intVal - b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.intVal - b.doubleVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.BYTE) {
            return new Value(ValueType.DOUBLE, a.doubleVal - b.byteVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.INT) {
            return new Value(ValueType.DOUBLE, a.doubleVal - b.intVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.doubleVal - b.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }

    private Value visitMultiplyNode(Node node) {
        Value a = visit(node.nodeA);
        Value b = visit(node.nodeB);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, a.byteVal * b.byteVal);
        } else if(a.type == ValueType.BYTE && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.byteVal * b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.BYTE) {
            return new Value(ValueType.INT, a.intVal * b.byteVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.intVal * b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.intVal * b.doubleVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.BYTE) {
            return new Value(ValueType.DOUBLE, a.doubleVal * b.byteVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.INT) {
            return new Value(ValueType.DOUBLE, a.doubleVal * b.intVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.doubleVal * b.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }

    private Value visitDivideNode(Node node) {
        Value a = visit(node.nodeA);
        Value b = visit(node.nodeB);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, a.byteVal / b.byteVal);
        } else if(a.type == ValueType.BYTE && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.byteVal / b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.BYTE) {
            return new Value(ValueType.INT, a.intVal / b.byteVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.intVal / b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.intVal / b.doubleVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.BYTE) {
            return new Value(ValueType.DOUBLE, a.doubleVal / b.byteVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.INT) {
            return new Value(ValueType.DOUBLE, a.doubleVal / b.intVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.doubleVal / b.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }

    private Value visitModNode(Node node) {
        Value a = visit(node.nodeA);
        Value b = visit(node.nodeB);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, a.byteVal % b.byteVal);
        } else if(a.type == ValueType.BYTE && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.byteVal % b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.BYTE) {
            return new Value(ValueType.INT, a.intVal % b.byteVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.INT) {
            return new Value(ValueType.INT, a.intVal % b.intVal);
        } else if(a.type == ValueType.INT && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.intVal % b.doubleVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.BYTE) {
            return new Value(ValueType.DOUBLE, a.doubleVal % b.byteVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.INT) {
            return new Value(ValueType.DOUBLE, a.doubleVal % b.intVal);
        } else if(a.type == ValueType.DOUBLE && b.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, a.doubleVal % b.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }
        
        return null;
    }

    private Value visitPlusNode(Node node) {
        Value a = visit(node.nodeA);

        if(a.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, +a.byteVal);
        } else if(a.type == ValueType.INT) {
            return new Value(ValueType.INT, +a.intVal);
        } else if(a.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, +a.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }

    private Value visitMinusNode(Node node) {
        Value a = visit(node.nodeA);

        if(a.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, -a.byteVal);
        } else if(a.type == ValueType.INT) {
            return new Value(ValueType.INT, -a.intVal);
        } else if(a.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, -a.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }
}