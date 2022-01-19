package com.nirvanaself.pluto;

import java.util.List;
import java.util.ArrayList;

public class Parser {
    private String filename;
    private List<Token> tokens = new ArrayList<>();
    private int index = 0;

    public Parser(String filename, List<Token> tokens) {
        this.filename = filename;
        this.tokens = tokens;
        this.index = 0;
    }

    // public void advance() {
    //     index++;
    // }

    private void error() {
        Errors.invalidSyntax(filename, current().line);
    }

    private Token current() {
        return tokens.get(index);
    }
    
    private void eat(TokenType type) {
        if(current().type == type) {
            index++;
        } else {
            error();
        }
    }

    public Node parse() {
        Node result = stmtList();
        
        eat(TokenType.EOF);
        
        return result;
    }

    private Node stmtList() {
        return stmtList(TokenType.EOF);
    }

    private Node stmtList(TokenType end) {
        if (current().type == end) {
            return new Node(current().line, NodeType.EmptyNode);
        }
        
        int line = current().line;
    
        List<Node> stmts = new ArrayList<>();

        while(current().type != end) {
            stmts.add(stmt());
        }

        return new Node(current().line, NodeType.StmtListNode, stmts);
    }

    private Node stmt() {
        if(current().type == TokenType.VAR) {
            return varStmt();
        } else if(current().type == TokenType.LCURLY) {
            return blockStmt();
        } else if(current().type == TokenType.IF) {
            return ifStmt();
        }

        Node result = exp();
        
        eat(TokenType.SEMICOLON);

        return result;
    }


    private Node ifStmt() {
        int line = current().line;

        eat(TokenType.IF);

        Node cond = parenExp();

        eat(TokenType.LCURLY);

        Node stmtList = stmtList(TokenType.RCURLY);

        eat(TokenType.RCURLY);

        return new Node(line, NodeType.IfStmtNode, cond, stmtList);
    }

    private Node blockStmt() {
        int line = current().line;

        eat(TokenType.LCURLY);

        Node stmtList = stmtList(TokenType.RCURLY);

        eat(TokenType.RCURLY);

        return new Node(line, NodeType.BlockStmtNode, stmtList);
    }

    private Node varStmt() {
        int line = current().line;
        eat(TokenType.VAR);

        String name = current().id;

        eat(TokenType.NAME);

        eat(TokenType.EQ);

        Node val = exp();

        eat(TokenType.SEMICOLON);

        return new Node(line, NodeType.VarStmtNode, name, val);
    }

    private Node exp() {
        return assignExp();
    }

    private Node assignExp() {
        Node result = compExp();

        if(current().type == TokenType.EQ) {
            eat(TokenType.EQ);

            result = new Node(result.line, NodeType.AssignNode, result, assignExp());
        }

        return result;
    }

    private Node compExp() {
        Node result = addExp();

        while((current().type == TokenType.LT || current().type == TokenType.EE 
               || current().type == TokenType.GT)
               && current().type != TokenType.EOF) {

            if(current().type == TokenType.LT) {
                eat(TokenType.LT);
                result = new Node(result.line, NodeType.LTNode, result, addExp());
            } else if(current().type == TokenType.EE) {
                eat(TokenType.EE);
                result = new Node(result.line, NodeType.EENode, result, addExp());
            } else {
                eat(TokenType.GT);
                result = new Node(result.line, NodeType.GTNode, result, addExp());
            }
        }
         
        return result;
    }

    private Node addExp() {
        Node result = multiplyExp();

        while((current().type == TokenType.PLUS || current().type == TokenType.MINUS)
               && current().type != TokenType.EOF) {
                   
            if(current().type == TokenType.PLUS) {
                eat(TokenType.PLUS);
                result = new Node(result.line, NodeType.AddNode, result, multiplyExp());
            } else {
                eat(TokenType.MINUS);
                result = new Node(result.line, NodeType.SubtractNode, result, multiplyExp());
            }

        }
         
        return result;
    }

    private Node multiplyExp() {
        Node result = unaryExp();

        while((current().type == TokenType.MULTIPLY || current().type == TokenType.DIVIDE 
               || current().type == TokenType.MOD)
               && current().type != TokenType.EOF) {

            if(current().type == TokenType.MULTIPLY) {
                eat(TokenType.MULTIPLY);
                result = new Node(result.line, NodeType.MultiplyNode, result, unaryExp());
            } else if(current().type == TokenType.DIVIDE) {
                eat(TokenType.DIVIDE);
                result = new Node(result.line, NodeType.DivideNode, result, unaryExp());
            } else {
                eat(TokenType.MOD);
                result = new Node(result.line, NodeType.ModNode, result, unaryExp());
            }
        }
         
        return result;
    }

    private Node unaryExp() {
        Token token = current();

        if (current().type == TokenType.PLUS) {
            eat(TokenType.PLUS);
            Node expr = exp();

            return new Node(token.line, NodeType.PlusNode, expr);
        } else if(current().type == TokenType.MINUS) {
            eat(TokenType.MINUS);
            Node expr = exp();

            return new Node(token.line, NodeType.MinusNode, expr);
        } else {
            if (current().type == TokenType.LPAREN) {
                return parenExp();
            } else {
                return basicExp();
            }
        }
    }

    private Node parenExp() {
        eat(TokenType.LPAREN);

        Node result = exp();

        eat(TokenType.RPAREN);

        return result;
    }

    private Node basicExp() {
        Token token = current();

        if(token.type == TokenType.TRUE) {
            eat(TokenType.TRUE);
            return new Node(token.line, NodeType.TrueNode);
        } else if(token.type == TokenType.FALSE) {
            eat(TokenType.FALSE);
            return new Node(token.line, NodeType.FalseNode);
        } else if(token.type == TokenType.BYTE) {
            eat(TokenType.BYTE);
            return new Node(token.line, NodeType.ByteNode, token.byteVal);
        } else if (token.type == TokenType.INT) {
            eat(TokenType.INT);
            return new Node(token.line, NodeType.IntNode, token.intVal);
        } else if(token.type == TokenType.DOUBLE) {
            eat(TokenType.DOUBLE);
            return new Node(token.line, NodeType.DoubleNode, token.doubleVal);
        } else if(token.type == TokenType.NAME) {
            eat(TokenType.NAME);            
            return new Node(token.line, NodeType.NameNode, token.id);
        } else {
            error();
        }

        return null;
    }
}