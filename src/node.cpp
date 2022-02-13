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
        return Int;
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
        return Double;
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
        return String;
    }

    std::string StringNode::to_string()
    {
        return string_val;
    }

    AddNode::AddNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind AddNode::kind()
    {
        return Add;
    }

    std::string AddNode::to_string()
    {
        return "("+node_a.get()->to_string()+" + "+node_b.get()->to_string()+")";
    }

    SubtractNode::SubtractNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind SubtractNode::kind()
    {
        return Subtract;
    }

    std::string SubtractNode::to_string()
    {
        return "("+node_a.get()->to_string()+" - "+node_b.get()->to_string()+")";
    }

    MultiplyNode::MultiplyNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind MultiplyNode::kind()
    {
        return Multiply;
    }

    std::string MultiplyNode::to_string()
    {
        return "("+node_a.get()->to_string()+" * "+node_b.get()->to_string()+")";
    }    

    DivideNode::DivideNode(int line, std::unique_ptr<Node> node_a, std::unique_ptr<Node> node_b)
    {
        this->node_a = std::move(node_a);
        this->node_b = std::move(node_b);
    }

    NodeKind DivideNode::kind()
    {
        return Divide;
    }

    std::string DivideNode::to_string()
    {
        return "("+node_a.get()->to_string()+" / "+node_b.get()->to_string()+")";
    } 

    PlusNode::PlusNode(int line, std::unique_ptr<Node> node)
    {
        this->node = std::move(node);
    }

    NodeKind PlusNode::kind()
    {
        return Plus;
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
        return Minus;
    }

    std::string MinusNode::to_string()
    {
        return "(- "+node.get()->to_string()+")";
    }     
}