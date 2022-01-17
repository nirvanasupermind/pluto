package com.nirvanaself.pluto;

public class Node {
    public int line = 0;
    public NodeType type;
    public Node nodeA;
    public Node nodeB;
    public int intVal = 0;
    public double doubleVal = 0.0;


    public Node(int line, NodeType type) {
        this.line = line;
        this.type = type;
    }
    
    public Node(int line, NodeType type, int intVal) {
        this.line = line;
        this.type = type;
        this.intVal = intVal;
    }

    public Node(int line, NodeType type, double doubleVal) {
        this.line = line;
        this.type = type;
        this.doubleVal = doubleVal;
    }

    public Node(int line, NodeType type, Node nodeA) {
        this.line = line;
        this.type = type;
        this.nodeA = nodeA;
    }

    public Node(int line, NodeType type, Node nodeA, Node nodeB) {
        this.line = line;
        this.type = type;
        this.nodeA = nodeA;
        this.nodeB = nodeB;
    }

    @Override
    public String toString() {
        String result = "";

        switch(type) {
            case IntNode:
                result = String.valueOf(intVal);
                break;
            case DoubleNode:
                result = String.valueOf(doubleVal);
                break;
            case AddNode:
                result = String.format("(%s + %s)", nodeA.toString(), nodeB.toString());
                break;
            case SubtractNode:
                result = String.format("(%s - %s)", nodeA.toString(), nodeB.toString());
                break;
            case MultiplyNode:
                result = String.format("(%s * %s)", nodeA.toString(), nodeB.toString());
                break;
            case DivideNode:
                result = String.format("(%s / %s)", nodeA.toString(), nodeB.toString());
                break;
            case ModNode:
                result = String.format("(%s %% %s)", nodeA.toString(), nodeB.toString());
                break;
            case PlusNode:
                result = String.format("(+ %s)", nodeA.toString());
                break;
            case MinusNode:
                result = String.format("(- %s)", nodeA.toString());
                break;
            default:
                result = "()";
                break;
        }

        return result;
    }
}