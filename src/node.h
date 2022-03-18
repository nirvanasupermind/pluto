#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>
#include <vector>

#include "token.h"

namespace pluto
{
    enum NodeKind
    {
        PROGRAM_NODE,
        BYTE_NODE,
        INT_NODE,
        DOUBLE_NODE,
        STRING_NODE,
        NAME_NODE,
        TRUE_NODE,
        FALSE_NODE,
        NIL_NODE,
        ADD_NODE,
        SUBTRACT_NODE,
        MULTIPLY_NODE,
        DIVIDE_NODE,
        MOD_NODE,
        OR_NODE,
        AND_NODE,
        XOR_NODE,
        BOR_NODE,
        BAND_NODE,
        BXOR_NODE,
        LSHIFT_NODE,
        RSHIFT_NODE,
        EE_NODE,
        NE_NODE,
        LT_NODE,
        GT_NODE,
        LTE_NODE,
        GTE_NODE,
        ASSIGN_NODE,
        PLUS_NODE,
        MINUS_NODE,
        NOT_NODE,
        BNOT_NODE,
        CALL_NODE,
        MEMBER_ACCESS_NODE,
        VAR_DEF_NODE,
        CONST_DEF_NODE,
        BLOCK_NODE,
        IF_NODE,
        IF_ELSE_NODE,
        FOR_NODE,
        WHILE_NODE,
        FUNC_DEF_NODE,
        RETURN_NODE,
        LAMBDA_NODE,
        CLASS_DEF_NODE,
        MODULE_DEF_NODE
    };

    class Node
    {
    public:
        int line;

        virtual NodeKind kind() = 0;
        
        virtual std::string to_string() = 0;
    };

    class ProgramNode : public Node
    {
    public:
        std::vector<std::shared_ptr<Node> > nodes;

        ProgramNode(int line, std::vector<std::shared_ptr<Node> > nodes);

        NodeKind kind();

        std::string to_string();
    };

    class ByteNode : public Node
    {
    public:
        signed char byte_val;

        ByteNode(int line, signed char byte_val);

        NodeKind kind();

        std::string to_string();
    };

    class IntNode : public Node
    {
    public:
        long int int_val;

        IntNode(int line, long int int_val);

        NodeKind kind();

        std::string to_string();
    };

    class DoubleNode : public Node
    {
    public:
        double double_val;        
        
        DoubleNode(int line, double double_val);

        NodeKind kind();

        std::string to_string();
    };

    class StringNode : public Node
    {
    public:
        std::string string_val;

        StringNode(int line, std::string string_val);

        NodeKind kind();

        std::string to_string();
    };

    class NameNode : public Node
    {
    public:
        std::string name;

        NameNode(int line, std::string name);

        NodeKind kind();

        std::string to_string();
    };

    class TrueNode : public Node
    {
    public:
        TrueNode(int line);

        NodeKind kind();

        std::string to_string();
    };

    class FalseNode : public Node
    {
    public:
        FalseNode(int line);

        NodeKind kind();

        std::string to_string();
    };

    class NilNode : public Node
    {
    public:
        NilNode(int line);

        NodeKind kind();

        std::string to_string();
    };

    class AddNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        AddNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };


    class SubtractNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        SubtractNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class MultiplyNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        MultiplyNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class DivideNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        DivideNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class ModNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        ModNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };


    class OrNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        OrNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class AndNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        AndNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class XorNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        XorNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class BOrNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        BOrNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class BAndNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        BAndNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class BXorNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        BXorNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class LShiftNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        LShiftNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class RShiftNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        RShiftNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class EENode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        EENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class NENode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        NENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class LTNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        LTNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };
    
    class GTNode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        GTNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class LTENode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        LTENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class GTENode : public Node
    {
    public:
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;

        GTENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b);

        NodeKind kind();

        std::string to_string();
    };

    class AssignNode : public Node
    {
    public:
        std::shared_ptr<Node> key;
        std::shared_ptr<Node> val;

        AssignNode(int line, std::shared_ptr<Node> key, std::shared_ptr<Node> val);

        NodeKind kind();

        std::string to_string();
    };

    class PlusNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        PlusNode(int line, std::shared_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };

    class MinusNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        MinusNode(int line, std::shared_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };

    class NotNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        NotNode(int line, std::shared_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };

    class BNotNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        BNotNode(int line, std::shared_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };

    class CallNode : public Node
    {
    public:
        std::shared_ptr<Node> callee;
        std::vector<std::shared_ptr<Node> > args;

        CallNode(int line, std::shared_ptr<Node> callee, std::vector<std::shared_ptr<Node> > args);

        NodeKind kind();

        std::string to_string();
    };

    class MemberAccessNode : public Node
    {
    public:
        std::shared_ptr<Node> subject;
        std::string member;

        MemberAccessNode(int line, std::shared_ptr<Node> subject, std::string member);

        NodeKind kind();

        std::string to_string();
    };

    class VarDefNode : public Node
    {
    public:
        std::string key;
        std::shared_ptr<Node> val;

        VarDefNode(int line, std::string key, std::shared_ptr<Node> val);

        NodeKind kind();

        std::string to_string();
    };

    class ConstDefNode : public Node
    {
    public:
        std::string key;
        std::shared_ptr<Node> val;

        ConstDefNode(int line, std::string key, std::shared_ptr<Node> val);

        NodeKind kind();

        std::string to_string();
    };

    class BlockNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        BlockNode(int line, std::shared_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };

    class IfNode : public Node
    {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> body;

        IfNode(int line, std::shared_ptr<Node> cond, std::shared_ptr<Node> body);

        NodeKind kind();

        std::string to_string();
    };

    class IfElseNode : public Node
    {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> body;
        std::shared_ptr<Node> else_body;

        IfElseNode(int line, std::shared_ptr<Node> cond, std::shared_ptr<Node> body, std::shared_ptr<Node> else_body);

        NodeKind kind();

        std::string to_string();
    };

    class ForNode : public Node
    {
    public:
        std::shared_ptr<Node> stmt_a;
        std::shared_ptr<Node> stmt_b;
        std::shared_ptr<Node> stmt_c;
        std::shared_ptr<Node> body;

        ForNode(int line, std::shared_ptr<Node> stmt_a, std::shared_ptr<Node> stmt_b, std::shared_ptr<Node> stmt_c, std::shared_ptr<Node> body);

        NodeKind kind();

        std::string to_string();
    };

    class WhileNode : public Node
    {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> body;

        WhileNode(int line, std::shared_ptr<Node> cond, std::shared_ptr<Node> body);

        NodeKind kind();

        std::string to_string();
    };

    class FuncDefNode : public Node
    {
    public:
        std::string name;
        std::vector<std::string> args;
        std::shared_ptr<Node> body;

        FuncDefNode(int line, std::string name, std::vector<std::string> &args, std::shared_ptr<Node> body);

        NodeKind kind();

        std::string to_string();
    };

    class ReturnNode : public Node
    {
    public:
        std::shared_ptr<Node> node;

        ReturnNode(int line, std::shared_ptr<Node> node);

        NodeKind kind();

        std::string to_string();
    };

    class LambdaNode : public Node
    {
    public:
        std::vector<std::string> args;
        std::shared_ptr<Node> body;

        LambdaNode(int line, std::vector<std::string> &args, std::shared_ptr<Node> body);

        NodeKind kind();

        std::string to_string();
    };

    class ClassDefNode : public Node
    {
    public:
        std::string name;
        std::shared_ptr<Node> body;

        ClassDefNode(int line, std::string name, std::shared_ptr<Node> body);

        NodeKind kind();

        std::string to_string();
    };

    class ModuleDefNode : public Node
    {
    public:
        std::string name;
        std::shared_ptr<Node> body;

        ModuleDefNode(int line, std::string name, std::shared_ptr<Node> body);

        NodeKind kind();

        std::string to_string();
    };
}

#endif