package com.nirvanaself.pluto;

public class Interpreter {
    private String filename;

    public Interpreter(String filename) {
        this.filename = filename;
    }

    public Value visit(Node node, Env env) {
        switch(node.type) {
            case EmptyNode:
                return new Value(ValueType.NIL);
            case ByteNode:
                return visitByteNode(node, env);
            case IntNode:
                return visitIntNode(node, env);
            case DoubleNode:
                return visitDoubleNode(node, env);
            case NameNode:
                return visitNameNode(node, env);
            case AddNode:
                return visitAddNode(node, env); 
            case SubtractNode:
                return visitSubtractNode(node, env); 
            case MultiplyNode:
                return visitMultiplyNode(node, env);
            case DivideNode:
                return visitDivideNode(node, env);
            case ModNode:
                return visitModNode(node, env);
            case AssignNode:
                return visitAssignNode(node, env);
            case PlusNode:
                return visitPlusNode(node, env);
            case MinusNode:
                return visitMinusNode(node, env);
            case VarStmtNode:
                return visitVarStmtNode(node, env);
            case BlockStmtNode:
                return visitBlockStmtNode(node, env);
            case StmtListNode:
                return visitStmtListNode(node, env);
            default:
                throw new RuntimeException("Unknown node type");
        }
    }

    private Value visitByteNode(Node node, Env env) {
        return new Value(ValueType.BYTE, node.byteVal);
    }
    
    private Value visitIntNode(Node node, Env env) {
        return new Value(ValueType.INT, node.intVal);
    }

    private Value visitDoubleNode(Node node, Env env) {
        return new Value(ValueType.DOUBLE, node.doubleVal);       
    }

    private Value visitNameNode(Node node, Env env) {
        String name = node.name;

        Value result = env.get(name);

        if(result == null) {
            Errors.variableIsNotDefined(filename, node.line, name);
        }

        return env.get(name);
    }
            
    private Value visitAddNode(Node node, Env env) {
        Value a = visit(node.nodeA, env);
        Value b = visit(node.nodeB, env);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, (byte)(a.byteVal + b.byteVal));
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

    private Value visitSubtractNode(Node node, Env env) {
        Value a = visit(node.nodeA, env);
        Value b = visit(node.nodeB, env);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, (byte)(a.byteVal - b.byteVal));
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

    private Value visitMultiplyNode(Node node, Env env) {
        Value a = visit(node.nodeA, env);
        Value b = visit(node.nodeB, env);

        if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, (byte)(a.byteVal * b.byteVal));
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

    private Value visitDivideNode(Node node, Env env) {
        Value a = visit(node.nodeA, env);
        Value b = visit(node.nodeB, env);

        try {

            if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
                return new Value(ValueType.BYTE, (byte)(a.byteVal / b.byteVal));
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

        } catch(ArithmeticException e) {
            Errors.divideByZero(filename, node.line);            
        }

        return null;
    }

    private Value visitModNode(Node node, Env env) {
        Value a = visit(node.nodeA, env);
        Value b = visit(node.nodeB, env);

        try {
            if(a.type == ValueType.BYTE && b.type == ValueType.BYTE) {
                return new Value(ValueType.BYTE, (byte)(a.byteVal % b.byteVal));
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
        } catch(ArithmeticException e) {
            Errors.modByZero(filename, node.line);            
        }
        
        return null;
    }

    private Value visitAssignNode(Node node, Env env) {
        if(node.nodeA.type != NodeType.NameNode) {
            Errors.invaildLeftHandSide(filename, node.line);
        }

        String name = node.nodeA.name;
        Value val = visit(node.nodeB, env);

        if(env.record.getOrDefault(name, null) == null) {
            Errors.variableIsNotDefined(filename, node.line, name);
        }

        env.put(name, val);

        return val;
    }

    private Value visitPlusNode(Node node, Env env) {
        Value a = visit(node.nodeA, env);

        if(a.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, (byte)+a.byteVal);
        } else if(a.type == ValueType.INT) {
            return new Value(ValueType.INT, +a.intVal);
        } else if(a.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, +a.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }

    private Value visitMinusNode(Node node, Env env) {
        Value a = visit(node.nodeA, env);

        if(a.type == ValueType.BYTE) {
            return new Value(ValueType.BYTE, (byte)-a.byteVal);
        } else if(a.type == ValueType.INT) {
            return new Value(ValueType.INT, -a.intVal);
        } else if(a.type == ValueType.DOUBLE) {
            return new Value(ValueType.DOUBLE, -a.doubleVal);
        } else {
            Errors.badOperandType(filename, node.line);
        }

        return null;
    }

    private Value visitVarStmtNode(Node node, Env env) {
        String name = node.name;
        Value val = visit(node.val, env);

        if(env.record.getOrDefault(name, null) != null) {
            Errors.variableIsAlreadyDefined(filename, node.line, name);
        }

        env.put(name, val);

        return val;
    }

    private Value visitBlockStmtNode(Node node, Env env) {
        Env blockEnv = new Env(env);

        return visit(node.nodeA, blockEnv);
    }

    private Value visitStmtListNode(Node node, Env env) {    
        for(int i = 0; i < node.stmts.size() - 1; i++) {
            visit(node.stmts.get(i), env);
        }

        return visit(node.stmts.get(node.stmts.size() - 1), env);
    }
}