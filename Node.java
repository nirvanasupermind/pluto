package com.github.pluto;

class Node {
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
        String result;

        switch(this.type) {
            case IntNode:
                result = String.format("%s", this.intVal);
                break;
            case DoubleNode:
                result = String.format("%s", this.doubleVal);
                break;
            case AddNode:
                result = String.format("(%s + %s)", this.nodeA.toString(), this.nodeB.toString());
                break;
            case SubtractNode:
                result = String.format("(%s - %s)", this.nodeA.toString(), this.nodeB.toString());
                break;
            case MultiplyNode:
                result = String.format("(%s * %s)", this.nodeA.toString(), this.nodeB.toString());
                break;
            case DivideNode:
                result = String.format("(%s / %s)", this.nodeA.toString(), this.nodeB.toString());
                break;
            case ModNode:
                result = String.format("(%s %% %s)", this.nodeA.toString(), this.nodeB.toString());
                break;
            case PlusNode:
                result = String.format("(+ %s)", this.nodeA.toString());
                break;
            case MinusNode:
                result = String.format("(- %s)", this.nodeA.toString());
                break;
            default:
                result = "()";
                break;
        }

        return result;
    }
}