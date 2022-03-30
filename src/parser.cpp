#include <string>
#include <memory>
#include <vector>

#include "token.h"
#include "node.h"
#include "parser.h"

namespace pluto
{
    Parser::Parser(std::string filename, std::vector<Token> tokens)
    {
        this->filename = filename;
        this->tokens = tokens;
        pos = 0;
    }

    void Parser::raise_error()
    {
        throw std::string(filename + ":" + std::to_string(current().line) + ": syntax error near token '" + current().str() + "'");
    }

    void Parser::advance()
    {
        pos++;
    }

    Token Parser::current()
    {
        return tokens.at(pos);
    }

    std::shared_ptr<Node> Parser::parse()
    {
        std::shared_ptr<Node> result = program();

        if (current().type != EOF_)
        {
            raise_error();
        }

        return result;
    }

    std::shared_ptr<Node> Parser::program(TokenType end)
    {
        int orig_line = current().line;

        std::vector<std::shared_ptr<Node> > nodes;

        while (current().type != end)
        {
            nodes.push_back(stmt());
        }

        return std::shared_ptr<Node>(new ProgramNode(orig_line, nodes));
    }

    std::shared_ptr<Node> Parser::stmt()
    {
        TokenType currenttype = current().type;

        if (currenttype == VAR)
        {
            return var_def_stmt();
        }

        if (currenttype == CONST)
        {
            return const_def_stmt();
        }

        if (currenttype == IF)
        {
            return if_stmt();
        }

        if (currenttype == FOR)
        {
            return for_stmt();
        }

        if (currenttype == WHILE)
        {
            return while_stmt();
        }

        if (currenttype == DEF)
        {
            return func_def_stmt();
        }

        if (currenttype == RETURN)
        {
            return return_stmt();
        }

        if (currenttype == CLASS)
        {
            return class_def_stmt();
        }

        if (currenttype == MODULE)
        {
            return module_def_stmt();
        }

        std::shared_ptr<Node> result = expr();

        if (current().type != SEMICOLON)
        {
            raise_error();
        }

        advance();

        return result;
    }

    std::shared_ptr<Node> Parser::module_def_stmt()
    {
        int orig_line = current().line;

        if (current().type != MODULE)
        {
            raise_error();
        }

        advance();
        
        if (current().type != NAME)
        {
            raise_error();
        }

        std::string name = current().name;

        advance();

        std::shared_ptr<Node> body = block_stmt();

        return std::shared_ptr<Node>(new ModuleDefNode(orig_line, name, body));
    }

    std::shared_ptr<Node> Parser::class_def_stmt()
    {
        int orig_line = current().line;

        if (current().type != CLASS)
        {
            raise_error();
        }

        advance();

        if (current().type != NAME)
        {
            raise_error();
        }

        std::string name = current().name;

        advance();

        std::shared_ptr<Node> body = block_stmt();

        return std::shared_ptr<Node>(new ClassDefNode(orig_line, name, body));
    }

    std::shared_ptr<Node> Parser::return_stmt()
    {
        if (current().type != RETURN)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> result = expr();

        if (current().type != SEMICOLON)
        {
            raise_error();
        }

        advance();

        return std::shared_ptr<Node>(new ReturnNode(result->line, result));
    }

    std::shared_ptr<Node> Parser::func_def_stmt()
    {
        int orig_line = current().line;

        if (current().type != DEF)
        {
            raise_error();
        }

        advance();

        if (current().type != NAME)
        {
            raise_error();
        }

        Token token = current();

        std::string name = token.name;

        advance();

        if (current().type != LPAREN)
        {
            raise_error();
        }

        advance();

        std::vector<std::string> args;

        if (current().type != RPAREN)
        {
            while (current().type != RPAREN)
            {
                Token token = current();

                if (current().type != NAME)
                {
                    raise_error();
                }

                args.push_back(token.name);

                advance();

                if (current().type != COMMA && current().type != RPAREN)
                {
                    raise_error();
                }

                if (current().type != RPAREN)
                {
                    advance();
                }
            }

            if (current().type != RPAREN)
            {
                raise_error();
            }

            advance();
        }
        else
        {
            advance();
        }

        std::shared_ptr<Node> body = block_stmt();

        return std::shared_ptr<Node>(new FuncDefNode(orig_line, name, args, body));
    }

    std::shared_ptr<Node> Parser::while_stmt()
    {
        int orig_line = current().line;

        if (current().type != WHILE)
        {
            raise_error();
        }

        advance();

        if (current().type != LPAREN)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> cond = expr();

        if (current().type != RPAREN)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> body = block_stmt();

        return std::shared_ptr<Node>(new WhileNode(orig_line, cond, body));
    }

    std::shared_ptr<Node> Parser::for_stmt()
    {
        int orig_line = current().line;

        if (current().type != FOR)
        {
            raise_error();
        }

        advance();

        if (current().type != LPAREN)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> stmt_a = stmt();
        std::shared_ptr<Node> stmt_b = stmt();
        std::shared_ptr<Node> stmt_c = stmt();

        if (current().type != RPAREN)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> body = block_stmt();

        return std::shared_ptr<Node>(new ForNode(orig_line, stmt_a, stmt_b, stmt_c, body));
    }

    std::shared_ptr<Node> Parser::if_stmt()
    {
        int orig_line = current().line;

        if (current().type != IF)
        {
            raise_error();
        }

        advance();

        if (current().type != LPAREN)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> cond = expr();

        if (current().type != RPAREN)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> body = block_stmt();

        if (current().type == ELSE)
        {
            advance();

            std::shared_ptr<Node> else_body = block_stmt();

            return std::shared_ptr<Node>(new IfElseNode(orig_line, cond, body, else_body));
        }

        return std::shared_ptr<Node>(new IfNode(orig_line, cond, body));
    }

    std::shared_ptr<Node> Parser::block_stmt()
    {
        int orig_line = current().line;

        if (current().type != LCURLY)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> node = program(RCURLY);

        if (current().type != RCURLY)
        {
            raise_error();
        }

        advance();

        return std::shared_ptr<Node>(new BlockNode(orig_line, node));
    }

    std::shared_ptr<Node> Parser::var_def_stmt()
    {
        int orig_line = current().line;

        if (current().type != VAR)
        {
            raise_error();
        }

        advance();

        if (current().type != NAME)
        {
            raise_error();
        }

        std::string key = current().name;

        advance();

        if (current().type != EQ)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> val = expr();

        if (current().type != SEMICOLON)
        {
            raise_error();
        }

        advance();

        return std::shared_ptr<Node>(new VarDefNode(orig_line, key, val));
    }

    std::shared_ptr<Node> Parser::const_def_stmt()
    {
        int orig_line = current().line;

        if (current().type != CONST)
        {
            raise_error();
        }

        advance();

        if (current().type != NAME)
        {
            raise_error();
        }

        std::string key = current().name;

        advance();

        if (current().type != EQ)
        {
            raise_error();
        }

        advance();

        std::shared_ptr<Node> val = expr();

        if (current().type != SEMICOLON)
        {
            raise_error();
        }

        advance();

        return std::shared_ptr<Node>(new ConstDefNode(orig_line, key, val));
    }

    std::vector<std::shared_ptr<Node> > Parser::expr_list(TokenType end)
    {
        std::vector<std::shared_ptr<Node> > nodes;

        if (current().type != end)
        {
            while (current().type != end)
            {
                Token token = current();

                nodes.push_back(expr());

                if (current().type != COMMA && current().type != end)
                {
                    raise_error();
                }

                if (current().type != end)
                {
                    advance();
                }
            }

            if (current().type != end)
            {
                raise_error();
            }

            advance();
        }
        else
        {
            advance();
        }

        return nodes;
    }

    std::shared_ptr<Node> Parser::expr()
    {
        return assign_expr();
    }

    std::shared_ptr<Node> Parser::assign_expr()
    {
        std::shared_ptr<Node> result = band_expr();

        if (current().type == EQ)
        {
            advance();
            result = std::shared_ptr<Node>(new AssignNode(result->line, result, assign_expr()));
        }

        return result;
    }

    std::shared_ptr<Node> Parser::band_expr()
    {
        std::shared_ptr<Node> result = bxor_expr();

        while (pos < tokens.size() && (current().type == BAND))
        {
            if (current().type == BAND)
            {
                advance();
                result = std::shared_ptr<Node>(new BAndNode(result->line, result, bxor_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::bxor_expr()
    {
        std::shared_ptr<Node> result = and_expr();

        while (pos < tokens.size() && (current().type == BXOR))
        {
            if (current().type == BXOR)
            {
                advance();
                result = std::shared_ptr<Node>(new BXorNode(result->line, result, bor_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::bor_expr()
    {
        std::shared_ptr<Node> result = and_expr();

        while (pos < tokens.size() && (current().type == BOR))
        {
            if (current().type == BOR)
            {
                advance();
                result = std::shared_ptr<Node>(new BOrNode(result->line, result, and_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::and_expr()
    {
        std::shared_ptr<Node> result = xor_expr();

        while (pos < tokens.size() && (current().type == AND))
        {
            if (current().type == AND)
            {
                advance();
                result = std::shared_ptr<Node>(new AndNode(result->line, result, xor_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::xor_expr()
    {
        std::shared_ptr<Node> result = or_expr();

        while (pos < tokens.size() && (current().type == XOR))
        {
            if (current().type == XOR)
            {
                advance();
                result = std::shared_ptr<Node>(new XorNode(result->line, result, or_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::or_expr()
    {
        std::shared_ptr<Node> result = shift_expr();

        while (pos < tokens.size() && (current().type == OR))
        {
            if (current().type == OR)
            {
                advance();
                result = std::shared_ptr<Node>(new OrNode(result->line, result, shift_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::shift_expr()
    {
        std::shared_ptr<Node> result = equality_expr();

        while (pos < tokens.size() && (current().type == LSHIFT || current().type == RSHIFT))
        {
            if (current().type == LSHIFT)
            {
                advance();
                result = std::shared_ptr<Node>(new LShiftNode(result->line, result, equality_expr()));
            }
            else if (current().type == RSHIFT)
            {
                advance();
                result = std::shared_ptr<Node>(new RShiftNode(result->line, result, equality_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::equality_expr()
    {
        std::shared_ptr<Node> result = comp_expr();

        while (pos < tokens.size() && (current().type == EE || current().type == NE))
        {
            if (current().type == EE)
            {
                advance();
                result = std::shared_ptr<Node>(new EENode(result->line, result, comp_expr()));
            }
            else if (current().type == NE)
            {
                advance();
                result = std::shared_ptr<Node>(new NENode(result->line, result, comp_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::comp_expr()
    {
        std::shared_ptr<Node> result = additive_expr();

        while (pos < tokens.size() && (current().type == LT || current().type == GT || current().type == LTE || current().type == GTE))
        {
            if (current().type == LT)
            {
                advance();
                result = std::shared_ptr<Node>(new LTNode(result->line, result, additive_expr()));
            }
            else if (current().type == GT)
            {
                advance();
                result = std::shared_ptr<Node>(new GTNode(result->line, result, additive_expr()));
            }
            else if (current().type == LTE)
            {
                advance();
                result = std::shared_ptr<Node>(new LTENode(result->line, result, additive_expr()));
            }
            else if (current().type == GTE)
            {
                advance();
                result = std::shared_ptr<Node>(new LTENode(result->line, result, additive_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::additive_expr()
    {
        std::shared_ptr<Node> result = multiplicative_expr();

        while (pos < tokens.size() && (current().type == PLUS || current().type == MINUS))
        {
            if (current().type == PLUS)
            {
                advance();
                result = std::shared_ptr<Node>(new AddNode(result->line, result, multiplicative_expr()));
            }
            else if (current().type == MINUS)
            {
                advance();
                result = std::shared_ptr<Node>(new SubtractNode(result->line, result, multiplicative_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::multiplicative_expr()
    {
        std::shared_ptr<Node> result = prefix_expr();

        while (pos < tokens.size() && (current().type == MULTIPLY || current().type == DIVIDE || current().type == MOD))
        {
            if (current().type == MULTIPLY)
            {
                advance();
                result = std::shared_ptr<Node>(new MultiplyNode(result->line, result, prefix_expr()));
            }
            else if (current().type == DIVIDE)
            {
                advance();
                result = std::shared_ptr<Node>(new DivideNode(result->line, result, prefix_expr()));
            }
            else if (current().type == MOD)
            {
                advance();
                result = std::shared_ptr<Node>(new ModNode(result->line, result, prefix_expr()));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::prefix_expr()
    {
        Token current_token = current();

        if (current_token.type == PLUS)
        {
            advance();
            return std::shared_ptr<Node>(new PlusNode(current_token.line, prefix_expr()));
        }
        else if (current_token.type == MINUS)
        {
            advance();
            return std::shared_ptr<Node>(new MinusNode(current_token.line, prefix_expr()));
        }
        else if (current_token.type == NOT)
        {
            advance();
            return std::shared_ptr<Node>(new NotNode(current_token.line, prefix_expr()));
        }
        else if (current_token.type == BNOT)
        {
            advance();
            return std::shared_ptr<Node>(new BNotNode(current_token.line, prefix_expr()));
        }

        return postfix_expr();
    }

    std::shared_ptr<Node> Parser::postfix_expr()
    {
        std::shared_ptr<Node> result = leaf_expr();

        while (current().type == LPAREN || current().type == DOT || current().type == LBRACKET)
        {
            TokenType currenttype = current().type;

            if (currenttype == LPAREN)
            {
                advance();

                std::vector<std::shared_ptr<Node> > args = expr_list();

                result = std::shared_ptr<Node>(new CallNode(result->line, result, args));
            }
            else if (currenttype == DOT)
            {
                advance();

                if (current().type != NAME)
                {
                    raise_error();
                }

                std::string prop = current().name;

                advance();

                result = std::shared_ptr<Node>(new MemberAccessNode(result->line, result, prop));
            }
        }

        return result;
    }

    std::shared_ptr<Node> Parser::leaf_expr()
    {
        Token current_token = current();

        if (current_token.type == LPAREN)
        {
            advance();

            std::shared_ptr<Node> result = expr();

            if (current().type != RPAREN)
            {
                raise_error();
            }

            advance();

            return result;
        }
        else if (current_token.type == INT)
        {
            advance();
            return std::shared_ptr<Node>(new IntNode(current_token.line, current_token.int_val));
        }
        else if (current_token.type == DOUBLE)
        {
            advance();
            return std::shared_ptr<Node>(new DoubleNode(current_token.line, current_token.double_val));
        }
        else if (current_token.type == CHAR)
        {
            advance();
            return std::shared_ptr<Node>(new CharNode(current_token.line, current_token.char_val));
        }
        else if (current_token.type == STRING)
        {
            advance();
            return std::shared_ptr<Node>(new StringNode(current_token.line, current_token.string_val));
        }
        else if (current_token.type == NAME)
        {
            advance();
            return std::shared_ptr<Node>(new NameNode(current_token.line, current_token.name));
        }
        else if (current_token.type == TRUE)
        {
            advance();
            return std::shared_ptr<Node>(new TrueNode(current_token.line));
        }
        else if (current_token.type == FALSE)
        {
            advance();
            return std::shared_ptr<Node>(new FalseNode(current_token.line));
        }
        else if (current_token.type == NIL)
        {
            advance();
            return std::shared_ptr<Node>(new NilNode(current_token.line));
        }
        else if (current_token.type == LAMBDA)
        {
            advance();

            if (current().type != LPAREN)
            {
                raise_error();
            }

            advance();

            std::vector<std::string> args;

            if (current().type != RPAREN)
            {
                while (current().type != RPAREN)
                {
                    Token token = current();

                    if (current().type != NAME)
                    {
                        raise_error();
                    }

                    args.push_back(token.name);

                    advance();

                    if (current().type != COMMA && current().type != RPAREN)
                    {
                        raise_error();
                    }

                    if (current().type != RPAREN)
                    {
                        advance();
                    }
                }

                if (current().type != RPAREN)
                {
                    raise_error();
                }

                advance();
            }
            else
            {
                advance();
            }

            if(current().type != LCURLY) {
                std::shared_ptr<Node> body = expr();

                return std::shared_ptr<Node>(new LambdaNode(current_token.line, args, body));
            }

            std::shared_ptr<Node> body = block_stmt();

            return std::shared_ptr<Node>(new LambdaNode(current_token.line, args, body));
        }

        raise_error();
    }
}