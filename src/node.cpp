#include <string>
#include <memory>
#include <vector>

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

    std::string ProgramNode::to_string()
    {
        std::string result = "(program";
        for (int i = 0; i < nodes.size(); i++)
        {
            result += "\t" + nodes[i]->to_string() + "\n";
        }

        result.pop_back();

        result += ')';

        return result;
    }

    IntNode::IntNode(int line, long int int_val)
    {
        this->line = line;
        this->int_val = int_val;
    }

    NodeKind IntNode::kind()
    {
        return INT_NODE;
    }

    std::string IntNode::to_string()
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

    std::string DoubleNode::to_string()
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

    std::string CharNode::to_string()
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

    std::string StringNode::to_string()
    {
        return "\"" + string_val + "\"";
    }

    ArrayNode::ArrayNode(int line, std::vector<std::shared_ptr<Node> > elems)
    {
        this->line = line;
        this->elems = elems;
    }

    NodeKind ArrayNode::kind()
    {
        return ARRAY_NODE;
    }

    std::string ArrayNode::to_string()
    {
        std::string result = "(array";
        for (int i = 0; i < elems.size(); i++)
        {
            result += " " + elems[i]->to_string() + "\n";
        }

        result.pop_back();

        result += ')';

        return result;
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

    std::string NameNode::to_string()
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

    std::string TrueNode::to_string()
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

    std::string FalseNode::to_string()
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

    std::string NilNode::to_string()
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

    std::string VarDefNode::to_string()
    {
        return "(var " + key + " " + val->to_string() + ")";
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

    std::string ConstDefNode::to_string()
    {
        return "(const " + key + " " + val->to_string() + ")";
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

    std::string AddNode::to_string()
    {
        return "(+ " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string SubtractNode::to_string()
    {
        return "(- " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string MultiplyNode::to_string()
    {
        return "(* " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string DivideNode::to_string()
    {
        return "(/ " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string ModNode::to_string()
    {
        return "(% " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string OrNode::to_string()
    {
        return "(|| " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string AndNode::to_string()
    {
        return "(&& " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string XorNode::to_string()
    {
        return "(^^ " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string BOrNode::to_string()
    {
        return "(| " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string BAndNode::to_string()
    {
        return "(& " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string BXorNode::to_string()
    {
        return "(^ " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string LShiftNode::to_string()
    {
        return "(<< " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string RShiftNode::to_string()
    {
        return "(>> " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string EENode::to_string()
    {
        return "(== " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string NENode::to_string()
    {
        return "(!= " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string LTNode::to_string()
    {
        return "(< " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string LTENode::to_string()
    {
        return "(<= " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string GTNode::to_string()
    {
        return "(> " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string GTENode::to_string()
    {
        return "(>= " + node_a->to_string() + " " + node_b->to_string() + ")";
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

    std::string AssignNode::to_string()
    {
        return "(= " + key->to_string() + " " + val->to_string() + ")";
    }

    PlusNode::PlusNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind PlusNode::kind()
    {
        return PLUS_NODE;
    }

    std::string PlusNode::to_string()
    {
        return "(+ " + node->to_string() + ")";
    }

    MinusNode::MinusNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind MinusNode::kind()
    {
        return MINUS_NODE;
    }

    std::string MinusNode::to_string()
    {
        return "(- " + node->to_string() + ")";
    }

    NotNode::NotNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind NotNode::kind()
    {
        return NOT_NODE;
    }

    std::string NotNode::to_string()
    {
        return "(! " + node->to_string() + ")";
    }

    BNotNode::BNotNode(int line, std::shared_ptr<Node> node)
    {
        this->node = node;
    }

    NodeKind BNotNode::kind()
    {
        return BNOT_NODE;
    }

    std::string BNotNode::to_string()
    {
        return "(~ " + node->to_string() + ")";
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

    std::string CallNode::to_string()
    {
        std::string result = "(" + callee->to_string();
        for (int i = 0; i < args.size(); i++)
        {
            result += " " + args[i]->to_string() + "\n";
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

    std::string MemberAccessNode::to_string()
    {
        return "(member-access " + subject->to_string() + " " + member + ")";
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

    std::string BlockNode::to_string()
    {
        return "(block " + node->to_string() + ")";
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

    std::string IfNode::to_string()
    {
        return "(if " + cond->to_string() + " " + body->to_string() + ")";
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

    std::string IfElseNode::to_string()
    {
        return "(if-else " + cond->to_string() + " " + body->to_string() + ")";
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

    std::string ForNode::to_string()
    {
        return "(for " + stmt_a->to_string() + " " + stmt_b->to_string() + " " + stmt_c->to_string() + " " + body->to_string() + ")";
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

    std::string WhileNode::to_string()
    {
        return "(while " + cond->to_string() + " " + body->to_string() + ")";
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

    std::string FuncDefNode::to_string()
    {
        std::string result = "(func (" + name;

        for (int i = 0; i < args.size(); i++)
        {
            result += " " + args[i];
        }

        result += ')';
        result += body->to_string();
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

    std::string ReturnNode::to_string()
    {
        return "(return " + node->to_string() + ")";
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

    std::string LambdaNode::to_string()
    {
        std::string result = "(lambda (";

        for (int i = 0; i < args.size(); i++)
        {
            result += " " + args[i];
        }

        result += ')';
        result += body->to_string();
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

    std::string ClassDefNode::to_string()
    {
        std::string result = "(class " + name + " ";

        result += body->to_string();
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

    std::string ModuleDefNode::to_string()
    {
        std::string result = "(module " + name + " ";

        result += body->to_string();
        result += ')';

        return result;
    }
}