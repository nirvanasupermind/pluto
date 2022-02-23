#include <string>
#include <memory>

#include "token.h"
#include "node.h"

namespace pluto
{

    IntNode::IntNode(int line, int int_val)
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

    AddNode::AddNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind AddNode::kind()
    {
        return ADD_NODE;
    }

    std::string AddNode::to_string()
    {
        return "("+node_a.get()->to_string()+" + "+node_b.get()->to_string()+")";
    }

    SubtractNode::SubtractNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind SubtractNode::kind()
    {
        return SUBTRACT_NODE;
    }

    std::string SubtractNode::to_string()
    {
        return "("+node_a.get()->to_string()+" - "+node_b.get()->to_string()+")";
    }

    MultiplyNode::MultiplyNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind MultiplyNode::kind()
    {
        return MULTIPLY_NODE;
    }

    std::string MultiplyNode::to_string()
    {
        return "("+node_a.get()->to_string()+" * "+node_b.get()->to_string()+")";
    }    

    DivideNode::DivideNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind DivideNode::kind()
    {
        return DIVIDE_NODE;
    }

    std::string DivideNode::to_string()
    {
        return "("+node_a.get()->to_string()+" / "+node_b.get()->to_string()+")";
    } 

    ModNode::ModNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind ModNode::kind()
    {
        return MOD_NODE;
    }

    std::string ModNode::to_string()
    {
        return "("+node_a.get()->to_string()+" % "+node_b.get()->to_string()+")";
    } 

    OrNode::OrNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind OrNode::kind()
    {
        return OR_NODE;
    }

    std::string OrNode::to_string()
    {
        return "("+node_a.get()->to_string()+" || "+node_b.get()->to_string()+")";
    } 

    AndNode::AndNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind AndNode::kind()
    {
        return AND_NODE;
    }

    std::string AndNode::to_string()
    {
        return "("+node_a.get()->to_string()+" && "+node_b.get()->to_string()+")";
    } 

    XorNode::XorNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind XorNode::kind()
    {
        return XOR_NODE;
    }

    std::string XorNode::to_string()
    {
        return "("+node_a.get()->to_string()+" ^^ "+node_b.get()->to_string()+")";
    } 

    BOrNode::BOrNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind BOrNode::kind()
    {
        return BOR_NODE;
    }

    std::string BOrNode::to_string()
    {
        return "("+node_a.get()->to_string()+" | "+node_b.get()->to_string()+")";
    } 

    BAndNode::BAndNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind BAndNode::kind()
    {
        return BAND_NODE;
    }

    std::string BAndNode::to_string()
    {
        return "("+node_a.get()->to_string()+" & "+node_b.get()->to_string()+")";
    } 

    BXorNode::BXorNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind BXorNode::kind()
    {
        return BXOR_NODE;
    }

    std::string BXorNode::to_string()
    {
        return "("+node_a.get()->to_string()+" ^ "+node_b.get()->to_string()+")";
    } 

    LShiftNode::LShiftNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind LShiftNode::kind()
    {
        return LSHIFT_NODE;
    }

    std::string LShiftNode::to_string()
    {
        return "("+node_a.get()->to_string()+" << "+node_b.get()->to_string()+")";
    } 
    
    RShiftNode::RShiftNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind RShiftNode::kind()
    {
        return RSHIFT_NODE;
    }

    std::string RShiftNode::to_string()
    {
        return "("+node_a.get()->to_string()+" >> "+node_b.get()->to_string()+")";
    } 

    LTNode::LTNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->line = line;
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind LTNode::kind()
    {
        return LT_NODE;
    }

    std::string LTNode::to_string()
    {
        return "("+node_a.get()->to_string()+" < "+node_b.get()->to_string()+")";
    } 

    PlusNode::PlusNode(int line, std::unique_ptr<Node> node)
    {
        this->node = std::move(node);
    }

    NodeKind PlusNode::kind()
    {
        return PLUS_NODE;
    }

    std::string PlusNode::to_string()
    {
        return "(+ "+node.get()->to_string()+")";
    } 

    MinusNode::MinusNode(int line, std::unique_ptr<Node> node)
    {
        this->node = std::move(node);
    }

    NodeKind MinusNode::kind()
    {
        return MINUS_NODE;
    }

    std::string MinusNode::to_string()
    {
        return "(- "+node.get()->to_string()+")";
    }   
    
    NotNode::NotNode(int line, std::unique_ptr<Node> node)
    {
        this->node = std::move(node);
    }

    NodeKind NotNode::kind()
    {
        return NOT_NODE;
    }

    std::string NotNode::to_string()
    {
        return "(! "+node.get()->to_string()+")";
    }  

    BNotNode::BNotNode(int line, std::unique_ptr<Node> node)
    {
        this->node = std::move(node);
    }

    NodeKind BNotNode::kind()
    {
        return BNOT_NODE;
    }

    std::string BNotNode::to_string()
    {
        return "(~ "+node.get()->to_string()+")";
    }  
}