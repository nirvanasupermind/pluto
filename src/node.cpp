#include <string>
#include <memory>
#include <vector>
#include <cstdint>

#include "token.h"
#include "node.h"

namespace pluto
{
    ProgramNode::ProgramNode(int line, std::vector<std::shared_ptr<Node> > nodes)
    {
        this->line = line;
        this->nodes = nodes;
    }

    NodeKind ProgramNode::kind()
    {
        return PROGRAM_NODE;
    }

    std::string ProgramNode::str()
    {
        std::string result = "(program";
        for (int i = 0; i < nodes.size(); i++)
        {
            result += "\t" + nodes[i]->str() + "\n";
        }

        result.pop_back();

        result += ')';

        return result;
    }

    IntNode::IntNode(int line, std::int32_t int_val)
    {
        this->line = line;
        this->int_val = int_val;
    }

    NodeKind IntNode::kind()
    {
        return INT_NODE;
    }

    std::string IntNode::str()
    {
        return std::to_string(int_val);
    }

    DoubleNode::DoubleNode(int line, double double_val)
    {
        this->line = line;
        this->double_val = double_val;
    }

    NodeKind DoubleNode::kind()
    {
        return DOUBLE_NODE;
    }

    std::string DoubleNode::str()
    {
        return std::to_string(double_val);
    }

    CharNode::CharNode(int line, unsigned char char_val)
    {
        this->line = line;
        this->char_val = char_val;
    }

    NodeKind CharNode::kind()
    {
        return CHAR_NODE;
    }

    std::string CharNode::str()
    {
        return std::to_string(char_val);
    }

    StringNode::StringNode(int line, std::string string_val)
    {
        this->line = line;
        this->string_val = string_val;
    }

    NodeKind StringNode::kind()
    {
        return STRING_NODE;
    }

    std::string StringNode::str()
    {
        return "\"" + string_val + "\"";
    }
    
    NameNode::NameNode(int line, std::string name)
    {
        this->line = line;
        this->name = name;
    }

    NodeKind NameNode::kind()
    {
        return NAME_NODE;
    }

    std::string NameNode::str()
    {
        return name;
    }

    TrueNode::TrueNode(int line)
    {
        this->line = line;
    }

    NodeKind TrueNode::kind()
    {
        return TRUE_NODE;
    }

    std::string TrueNode::str()
    {
        return "true";
    }

    FalseNode::FalseNode(int line)
    {
        this->line = line;
    }

    NodeKind FalseNode::kind()
    {
        return FALSE_NODE;
    }

    std::string FalseNode::str()
    {
        return "false";
    }

    NilNode::NilNode(int line)
    {
        this->line = line;
    }

    NodeKind NilNode::kind()
    {
        return NIL_NODE;
    }

    std::string NilNode::str()
    {
        return "nil";
    }

    VarDefNode::VarDefNode(int line, std::string key, std::shared_ptr<Node> val)
    {
        this->line = line;
        this->key = key;
        this->val = val;
    }

    NodeKind VarDefNode::kind()
    {
        return VAR_DEF_NODE;
    }

    std::string VarDefNode::str()
    {
        return "(var " + key + " " + val->str() + ")";
    }

    ConstDefNode::ConstDefNode(int line, std::string key, std::shared_ptr<Node> val)
    {
        this->line = line;
        this->key = key;
        this->val = val;
    }

    NodeKind ConstDefNode::kind()
    {
        return CONST_DEF_NODE;
    }

    std::string ConstDefNode::str()
    {
        return "(const " + key + " " + val->str() + ")";
    }

    AddNode::AddNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind AddNode::kind()
    {
        return ADD_NODE;
    }

    std::string AddNode::str()
    {
        return "(+ " + node_a->str() + " " + node_b->str() + ")";
    }

    SubtractNode::SubtractNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind SubtractNode::kind()
    {
        return SUBTRACT_NODE;
    }

    std::string SubtractNode::str()
    {
        return "(- " + node_a->str() + " " + node_b->str() + ")";
    }

    MultiplyNode::MultiplyNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind MultiplyNode::kind()
    {
        return MULTIPLY_NODE;
    }

    std::string MultiplyNode::str()
    {
        return "(* " + node_a->str() + " " + node_b->str() + ")";
    }

    DivideNode::DivideNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind DivideNode::kind()
    {
        return DIVIDE_NODE;
    }

    std::string DivideNode::str()
    {
        return "(/ " + node_a->str() + " " + node_b->str() + ")";
    }

    ModNode::ModNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind ModNode::kind()
    {
        return MOD_NODE;
    }

    std::string ModNode::str()
    {
        return "(% " + node_a->str() + " " + node_b->str() + ")";
    }

    OrNode::OrNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind OrNode::kind()
    {
        return OR_NODE;
    }

    std::string OrNode::str()
    {
        return "(|| " + node_a->str() + " " + node_b->str() + ")";
    }

    AndNode::AndNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind AndNode::kind()
    {
        return AND_NODE;
    }

    std::string AndNode::str()
    {
        return "(&& " + node_a->str() + " " + node_b->str() + ")";
    }

    XorNode::XorNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind XorNode::kind()
    {
        return XOR_NODE;
    }

    std::string XorNode::str()
    {
        return "(^^ " + node_a->str() + " " + node_b->str() + ")";
    }

    BOrNode::BOrNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind BOrNode::kind()
    {
        return BOR_NODE;
    }

    std::string BOrNode::str()
    {
        return "(| " + node_a->str() + " " + node_b->str() + ")";
    }

    BAndNode::BAndNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind BAndNode::kind()
    {
        return BAND_NODE;
    }

    std::string BAndNode::str()
    {
        return "(& " + node_a->str() + " " + node_b->str() + ")";
    }

    BXorNode::BXorNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind BXorNode::kind()
    {
        return BXOR_NODE;
    }

    std::string BXorNode::str()
    {
        return "(^ " + node_a->str() + " " + node_b->str() + ")";
    }

    LShiftNode::LShiftNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind LShiftNode::kind()
    {
        return LSHIFT_NODE;
    }

    std::string LShiftNode::str()
    {
        return "(<< " + node_a->str() + " " + node_b->str() + ")";
    }

    RShiftNode::RShiftNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind RShiftNode::kind()
    {
        return RSHIFT_NODE;
    }

    std::string RShiftNode::str()
    {
        return "(>> " + node_a->str() + " " + node_b->str() + ")";
    }

    EENode::EENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind EENode::kind()
    {
        return EE_NODE;
    }

    std::string EENode::str()
    {
        return "(== " + node_a->str() + " " + node_b->str() + ")";
    }

    NENode::NENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind NENode::kind()
    {
        return NE_NODE;
    }

    std::string NENode::str()
    {
        return "(!= " + node_a->str() + " " + node_b->str() + ")";
    }

    LTNode::LTNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind LTNode::kind()
    {
        return LT_NODE;
    }

    std::string LTNode::str()
    {
        return "(< " + node_a->str() + " " + node_b->str() + ")";
    }

    LTENode::LTENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind LTENode::kind()
    {
        return LTE_NODE;
    }

    std::string LTENode::str()
    {
        return "(<= " + node_a->str() + " " + node_b->str() + ")";
    }

    GTNode::GTNode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind GTNode::kind()
    {
        return GT_NODE;
    }

    std::string GTNode::str()
    {
        return "(> " + node_a->str() + " " + node_b->str() + ")";
    }

    GTENode::GTENode(int line, std::shared_ptr<Node> node_a, std::shared_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = node_a;
        this->node_b = node_b;
    }

    NodeKind GTENode::kind()
    {
        return GTE_NODE;
    }

    std::string GTENode::str()
    {
        return "(>= " + node_a->str() + " " + node_b->str() + ")";
    }

    AssignNode::AssignNode(int line, std::shared_ptr<Node> key, std::shared_ptr<Node> val)
    {
        this->line = line;
        this->key = key;
        this->val = val;
    }

    NodeKind AssignNode::kind()
    {
        return ASSIGN_NODE;
    }

    std::string AssignNode::str()
    {
        return "(= " + key->str() + " " + val->str() + ")";
    }

    PlusNode::PlusNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind PlusNode::kind()
    {
        return PLUS_NODE;
    }

    std::string PlusNode::str()
    {
        return "(+ " + node->str() + ")";
    }

    MinusNode::MinusNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind MinusNode::kind()
    {
        return MINUS_NODE;
    }

    std::string MinusNode::str()
    {
        return "(- " + node->str() + ")";
    }

    NotNode::NotNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind NotNode::kind()
    {
        return NOT_NODE;
    }

    std::string NotNode::str()
    {
        return "(! " + node->str() + ")";
    }

    BNotNode::BNotNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind BNotNode::kind()
    {
        return BNOT_NODE;
    }

    std::string BNotNode::str()
    {
        return "(~ " + node->str() + ")";
    }

    CallNode::CallNode(int line, std::shared_ptr<Node> callee, std::vector<std::shared_ptr<Node> > args)
    {
        this->line = line;
        this->callee = callee;
        this->args = args;
    }

    NodeKind CallNode::kind()
    {
        return CALL_NODE;
    }

    std::string CallNode::str()
    {
        std::string result = "(" + callee->str();
        for (int i = 0; i < args.size(); i++)
        {
            result += " " + args[i]->str() + "\n";
        }

        result.pop_back();

        result += ')';

        return result;
    }

    MemberAccessNode::MemberAccessNode(int line, std::shared_ptr<Node> subject, std::string member)
    {
        this->line = line;
        this->subject = subject;
        this->member = member;
    }

    NodeKind MemberAccessNode::kind()
    {
        return MEMBER_ACCESS_NODE;
    }

    std::string MemberAccessNode::str()
    {
        return "(member-access " + subject->str() + " " + member + ")";
    }

    BlockNode::BlockNode(int line, std::shared_ptr<Node> node)
    {
        this->line = line;
        this->node = node;
    }

    NodeKind BlockNode::kind()
    {
        return BLOCK_NODE;
    }

    std::string BlockNode::str()
    {
        return "(block " + node->str() + ")";
    }

    IfNode::IfNode(int line, std::shared_ptr<Node> cond, std::shared_ptr<Node> body)
    {
        this->line = line;
        this->cond = cond;
        this->body = body;
    }

    NodeKind IfNode::kind()
    {
        return IF_NODE;
    }

    std::string IfNode::str()
    {
        return "(if " + cond->str() + " " + body->str() + ")";
    }

    IfElseNode::IfElseNode(int line, std::shared_ptr<Node> cond, std::shared_ptr<Node> body, std::shared_ptr<Node> else_body)
    {
        this->line = line;
        this->cond = cond;
        this->body = body;
        this->else_body = else_body;
    }

    NodeKind IfElseNode::kind()
    {
        return IF_ELSE_NODE;
    }

    std::string IfElseNode::str()
    {
        return "(if-else " + cond->str() + " " + body->str() + ")";
    }

    ForNode::ForNode(int line, std::shared_ptr<Node> stmt_a, std::shared_ptr<Node> stmt_b, std::shared_ptr<Node> stmt_c, std::shared_ptr<Node> body)
    {
        this->line = line;
        this->stmt_a = stmt_a;
        this->stmt_b = stmt_b;
        this->stmt_c = stmt_c;
        this->body = body;
    }

    NodeKind ForNode::kind()
    {
        return FOR_NODE;
    }

    std::string ForNode::str()
    {
        return "(for " + stmt_a->str() + " " + stmt_b->str() + " " + stmt_c->str() + " " + body->str() + ")";
    }

    WhileNode::WhileNode(int line, std::shared_ptr<Node> cond, std::shared_ptr<Node> body)
    {
        this->line = line;
        this->cond = cond;
        this->body = body;
    }

    NodeKind WhileNode::kind()
    {
        return WHILE_NODE;
    }

    std::string WhileNode::str()
    {
        return "(while " + cond->str() + " " + body->str() + ")";
    }

    FuncDefNode::FuncDefNode(int line, std::string name, std::vector<std::string> &args, std::shared_ptr<Node> body)
    {
        this->line = line;
        this->name = name;
        this->args = args;
        this->body = body;
    }

    NodeKind FuncDefNode::kind()
    {
        return FUNC_DEF_NODE;
    }

    std::string FuncDefNode::str()
    {
        std::string result = "(func (" + name;

        for (int i = 0; i < args.size(); i++)
        {
            result += " " + args[i];
        }

        result += ')';
        result += body->str();
        result += ')';

        return result;
    }

    ReturnNode::ReturnNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind ReturnNode::kind()
    {
        return RETURN_NODE;
    }

    std::string ReturnNode::str()
    {
        return "(return " + node->str() + ")";
    }

    LambdaNode::LambdaNode(int line, std::vector<std::string> &args, std::shared_ptr<Node> body)
    {
        this->line = line;
        this->args = args;
        this->body = body;
    }

    NodeKind LambdaNode::kind()
    {
        return LAMBDA_NODE;
    }

    std::string LambdaNode::str()
    {
        std::string result = "(lambda (";

        for (int i = 0; i < args.size(); i++)
        {
            result += " " + args[i];
        }

        result += ')';
        result += body->str();
        result += ')';

        return result;
    }

    ClassDefNode::ClassDefNode(int line, std::string name, std::shared_ptr<Node> body)
    {
        this->line = line;
        this->name = name;
        this->body = body;
    }

    NodeKind ClassDefNode::kind()
    {
        return CLASS_DEF_NODE;
    }

    std::string ClassDefNode::str()
    {
        std::string result = "(class " + name + " ";

        result += body->str();
        result += ')';

        return result;
    }

    ModuleDefNode::ModuleDefNode(int line, std::string name, std::shared_ptr<Node> body)
    {
        this->line = line;
        this->name = name;
        this->body = body;
    }

    NodeKind ModuleDefNode::kind()
    {
        return MODULE_DEF_NODE;
    }

    std::string ModuleDefNode::str()
    {
        std::string result = "(module " + name + " ";

        result += body->str();
        result += ')';

        return result;
    }
}