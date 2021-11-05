#!/usr/bin/env lua

local WHITESPACE = " \n\t"
local DIGITS = "0123456789"
local PATH = (({...})[2] or arg[0]):gsub("[^/]*$", "")

function in_array(v, t)
    for i=1,#t do
      if v == t[i] then return true end
    end
end

function map(f, t)
    local t1 = {}
    local t_len = #t
    for i = 1, t_len do
        t1[i] = f(t[i])
    end
    return t1
end

function lexical_error(path, line)
    print("pluto: "..path..":"..line..": ".."lexical error")
    os.exit()
end

function syntax_error(path, line)
    print("pluto: "..path..":"..line..": ".."syntax error")
    os.exit()
end

function runtime_error(path, line)
    print("pluto: "..path..":"..line..": ".."runtime error")
    os.exit()
end

local Token = {}
Token.__index = Token

function Token:new(line, type, value)
    return setmetatable({
        line = line,
        type = type, 
        value = value
    }, self)
end

function Token:__tostring()
    if self.value ~= nil then return self.type..":"..self.value end
    return self.type
end

local Lexer = {}
Lexer.__index = Lexer

function Lexer:new(path, text)
    return setmetatable({
        path = path, 
        text = text.."\0", 
        index = 1,
        line = 1
    }, self)
end  

function Lexer:advance()
    self.index = self.index + 1
end

function Lexer:current() 
    return self.text:sub(self.index, self.index)
end

function Lexer:get_tokens()
    local tokens = {}

    while self:current() ~= "\0" do
        if string.find(WHITESPACE, self:current(), 1, true) then
            if self:current() == "\n" then 
                self.line = self.line + 1
            end
            self:advance()

        elseif string.find(DIGITS..".", self:current(), 1, true) then
            tokens[#tokens + 1] = self:get_number()

        elseif self:current() == "+" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "PLUS")

        elseif self:current() == "-" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "MINUS")

        elseif self:current() == "*" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "MULTIPLY")

        elseif self:current() == "/" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "DIVIDE")

        elseif self:current() == "(" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "LPAREN")

        elseif self:current() == ")" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "RPAREN")

        else
            lexical_error(self.path, self.line)
        end
    end

    tokens[#tokens + 1] = Token:new(self.line, "EOF")

    return tokens
end

function Lexer:get_number()
    local value = ""
    local decimal_point_count = 0
    
    while string.find(DIGITS..".", self:current(), 1, true) do
        if self:current() == "." then
            decimal_point_count = decimal_point_count + 1
            if decimal_point_count > 1 then break end
        end

        value = value..self:current()
        self:advance()
    end

    if value == "." then
        return Token:new(self.line, "DOT")
    end

    return Token:new(self.line, "NUMBER", tonumber(value))
end

local Node = {}
Node.__index = Node

function Node:new(line, sxp)
    return setmetatable({
        line = line, 
        sxp = sxp
    }, self)
end

function Node:__tostring()
    return "("..table.concat(map(tostring, self.sxp), " ")..")"
end

local Parser = {}
Parser.__index = Parser

function Parser:new(path, tokens)
    return setmetatable({
        path = path,
        tokens = tokens,
        index = 1
    }, self)
end

function Parser:advance()
    self.index = self.index + 1
end

function Parser:current()
    return self.tokens[self.index]
end

function Parser:parse()
    local result = self:expr()

    if self:current().type ~= "EOF" then
        syntax_error(self.path, self:current().line)
    end
    
    return result
end

function Parser:expr()
    return self:additive_expr()
end

function Parser:additive_expr()
    result = self:multiplicative_expr()

    while self:current().type ~= "EOF"
          and in_array(self:current().type, {"PLUS", "MINUS"}) do
            if self:current().type == "PLUS" then
                self:advance()
                result = Node:new(
                    result.line,
                    {"add", result, self:multiplicative_expr()}
                )
            else
                self:advance()
                result = Node:new(
                    result.line,
                    {"subtract", result, self:multiplicative_expr()}
                )
            end
    end

    return result
end

function Parser:multiplicative_expr()
    result = self:unary_expr()

    while self:current().type ~= "EOF"
          and in_array(self:current().type, {"MULTIPLY", "DIVIDE"}) do
            if self:current().type == "MULTIPLY" then
                self:advance()
                result = Node:new(
                    result.line,
                    {"multiply", result, self:unary_expr()}
                )
            else
                self:advance()
                result = Node:new(
                    result.line,
                    {"divide", result, self:unary_expr()}
                )
            end
    end

    return result
end

function Parser:unary_expr()
    token = self:current()

    if token.type == "MINUS" then
        self:advance()

        return Node:new(
            token.line, 
            {"minus", self:unary_expr()}
        )
    else
        return self:paren_expr()
    end
end

function Parser:paren_expr()
    if self:current().type == "LPAREN" then
        self:advance()

        expr = self:expr()

        if self:current().type ~= "RPAREN" then
            syntax_error(self.path, self:current().line)
        end

        self:advance()

        return expr
    else
        return self:leaf_expr()
    end
end

function Parser:leaf_expr()
    token = self:current()

    if self:current().type == "NUMBER" then
        self:advance()

        return Node:new(
            token.line,
            {"number", token.value}
        )
    else
        syntax_error(self.path, self:current().line)
    end
end

local Value = {}
Value.__index = Value

function Value:new(value)
    return setmetatable({
        value = value,
        id = math.random()
    }, self)
end

function Value:__tostring()
    return tostring(self.value)
end

local Interpreter = {}
Interpreter.__index = Interpreter

function Interpreter:new(path)
    return setmetatable({path = path}, Interpreter)
end

function Interpreter:eval(node)
    if node.sxp[1] == "number" then
        return Value:new(tonumber(node.sxp[2]))

    elseif node.sxp[1] == "add" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2]).value + self:eval(node.sxp[3]).value 
            end,
            node
        )

    elseif node.sxp[1] == "subtract" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2]).value - self:eval(node.sxp[3]).value 
            end,
            node
        )

    elseif node.sxp[1] == "multiply" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2]).value * self:eval(node.sxp[3]).value 
            end,
            node
        )

    elseif node.sxp[1] == "divide" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2]).value / self:eval(node.sxp[3]).value 
            end,
            node
        )

    elseif node.sxp[1] == "minus" then
        return self:eval_operation(
            function ()
                return -self:eval(node.sxp[2]).value
            end,
            node
        )

    else
        error("Unknown node type "..node.sxp[1], 2)
    end
end

function Interpreter:eval_operation(func, node)
    if pcall(func) == false then 
        runtime_error(self.path, node.line)
    else
        return Value:new(func())
    end
end

if #arg == 1 then
    local path = arg[1]
    local file = io.open(PATH..path, "rb")
    local text = file:read("*a")
    file:close()

    local lexer = Lexer:new(path, text)
    local tokens = lexer:get_tokens()

    local parser = Parser:new(path, tokens)
    local tree = parser:parse()

    local interpreter = Interpreter:new(path)
    local result = interpreter:eval(tree)

    print(result)
end