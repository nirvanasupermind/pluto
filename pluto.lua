#!/usr/bin/env lua

local WHITESPACE = " \n\t"
local DIGITS = "0123456789"
local LETTERS = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
local PATH = (({...})[2] or arg[0]):gsub("[^/]*$", "")
 
local function in_array(v, t)
    for i=1,#t do
      if v == t[i] then return true end
    end
end

local function map(f, t)
    local t1 = {}
    local t_len = #t
    for i = 1, t_len do
        t1[i] = f(t[i])
    end
    return t1
end

local function lexical_error(path, line)
    print("pluto: "..path..":"..line..": ".."lexical error")
    os.exit()
end

local function syntax_error(path, line)
    print("pluto: "..path..":"..line..": ".."syntax error")
    os.exit()
end

local function runtime_error(path, line)
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
        line = 1,
        keywords = {"null", "true", "false", "if", "else"}
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

        elseif string.find(LETTERS, self:current(), 1, true) then
            tokens[#tokens + 1] = self:get_name()

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

        elseif self:current() == "{" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "LCURLY")

        elseif self:current() == "}" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "RCURLY")

        elseif self:current() == "<" then
            self:advance()
            if self:current() == "=" then
                self:advance()
                tokens[#tokens + 1] = Token:new(self.line, "LE") 
            else               
                tokens[#tokens + 1] = Token:new(self.line, "LT")
            end

        elseif self:current() == "=" then
            self:advance()
            if self:current() == "=" then
                self:advance()
                tokens[#tokens + 1] = Token:new(self.line, "EE") 
            else               
                tokens[#tokens + 1] = Token:new(self.line, "EQ")
            end
        
        elseif self:current() == ">" then
            self:advance()
            if self:current() == "=" then
                self:advance()
                tokens[#tokens + 1] = Token:new(self.line, "GE") 
            else               
                tokens[#tokens + 1] = Token:new(self.line, "GT")
            end

        elseif self:current() == "!" then
            self:advance()
            if self:current() == "=" then
                self:advance()
                tokens[#tokens + 1] = Token:new(self.line, "NE") 
            else               
                tokens[#tokens + 1] = Token:new(self.line, "NOT")
            end

        elseif self:current() == "&" then
            self:advance()
            if self:current() == "&" then
                self:advance()
                tokens[#tokens + 1] = Token:new(self.line, "AND") 
            else      
                lexical_error(self.path, self.line)         
            end

        elseif self:current() == "|" then
            self:advance()

            if self:current() == "|" then
                self:advance()
                tokens[#tokens + 1] = Token:new(self.line, "OR") 
            else               
                lexical_error(self.path, self.line)
            end

        elseif self:current() == ";" then
            self:advance()
            tokens[#tokens + 1] = Token:new(self.line, "SEMICOLON")

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

function Lexer:get_name()
    local name = ""
    
    while string.find(LETTERS..DIGITS, self:current(), 1, true) do
        name = name..self:current()
        self:advance()
    end

    if in_array(name, self.keywords) then
        return Token:new(self.line, "KEYWORD", name)
    end

    return Token:new(self.line, "NAME", name)
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
    while self:current().type == "SEMICOLON" do
        self:advance()
    end

    if self:current().type == "EOF" then
        return Node:new(
            self:current().line,
            {"empty"}
        )
    end

    local result = self:statements()

    if self:current().type ~= "EOF" then
        syntax_error(self.path, self:current().line)
    end
    
    return result
end

function Parser:statements()
    local ln = self:current().line
    local statements = {self:expr()}

    while self:current().type ~= "EOF"
          and self:current().type == "SEMICOLON" do
        self:advance()
            
        while self:current().type == "SEMICOLON" do
            self:advance()
        end

        if self:current().type == "EOF" then
            break
        end

        statements[#statements + 1] = self:expr()
    end

    return Node:new(
        ln,
        {"statements", statements}
    )
end

function Parser:expr()
    return self:assignment_expr()
end

function Parser:assignment_expr()
    result = self:or_expr()

    if self:current().type == "EQ" then
        self:advance()
    
        return Node:new(
            result.line,
            {"assignment", result, self:expr()}
        )
    end

    return result
end

function Parser:or_expr()
    result = self:and_expr()

    while self:current().type ~= "EOF"
          and self:current().type == "OR" do
            self:advance()
            result = Node:new(
                result.line,
                {"or", result, self:and_expr()}
            )
    end

    return result
end

function Parser:and_expr()
    result = self:relational_expr()

    while self:current().type ~= "EOF"
          and self:current().type == "AND" do
            self:advance()
            result = Node:new(
                result.line,
                {"and", result, self:relational_expr()}
            )
    end

    return result
end

function Parser:relational_expr()
    result = self:equality_expr()

    while self:current().type ~= "EOF"
          and in_array(self:current().type, {"LT", "GT", "LE", "GE"}) do
            if self:current().type == "LT" then
                self:advance()
                result = Node:new(
                    result.line,
                    {"lt", result, self:equality_expr()}
                )
            elseif self:current().type == "GT" then
                self:advance()
                result = Node:new(
                    result.line,
                    {"gt", result, self:equality_expr()}
                )
            elseif self:current().type == "LE" then
                self:advance()
                result = Node:new(
                    result.line,
                    {"le", result, self:equality_expr()}
                )    
            else
                self:advance()
                result = Node:new(
                    result.line,
                    {"ge", result, self:multiplicative_expr()}
                )
            end
    end

    return result
end

function Parser:equality_expr()
    result = self:additive_expr()

    while self:current().type ~= "EOF"
          and in_array(self:current().type, {"EE", "NE"}) do
            if self:current().type == "EE" then
                self:advance()
                result = Node:new(
                    result.line,
                    {"eq", result, self:equality_expr()}
                )    
            else
                self:advance()
                result = Node:new(
                    result.line,
                    {"ne", result, self:multiplicative_expr()}
                )
            end
    end

    return result
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
    elseif token.type == "NOT" then
        self:advance()

        return Node:new(
            token.line, 
            {"not", self:unary_expr()}
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

    if token.type == "NUMBER" then
        self:advance()

        return Node:new(
            token.line,
            {"number", token.value}
        )

    elseif token.type == "KEYWORD" and token.value == "null" then
        self:advance()

        return Node:new(
            token.line,
            {"null"}
        )

    elseif token.type == "KEYWORD" and token.value == "true" then
        self:advance()

        return Node:new(
            token.line,
            {"true"}
        )

    elseif token.type == "KEYWORD" and token.value == "false" then
        self:advance()

        return Node:new(
            token.line,
            {"false"}
        )

    elseif token.type == "NAME" then
        self:advance()

        return Node:new(
            token.line,
            {"name", token.value}
        )

    elseif self:current().type == "KEYWORD" and self:current().value == "if" then
        return self:if_expr()

    else
        syntax_error(self.path, self:current().line)
    end
end

function Parser:curly_expr()
    if self:current().type ~= "LCURLY" then
        syntax_error(self.path, self:current().line)
    end

    self:advance() 

    while self:current().type == "SEMICOLON" do
        self:advance()
    end

    if self:current().type == "RCURLY" then
        return Node:new(
            self:current().line,
            {"empty"}
        )
    end
    
    expr = self:expr()

    if self:current().type ~= "RCURLY" then
        syntax_error(self.path, self:current().line)
    end

    return expr
end

function Parser:if_expr()
    self:advance()
    condition = self:expr()

    if_body = self:curly_expr()

    self:advance()

    if self:current().type == "KEYWORD" and self:current().value == "else" then
        self:advance()

        else_body = self:curly_expr()
        
        self:advance()
        return Node:new(
            condition.line,
            {"ifelse", condition, if_body, else_body}
        )
    end
    
    self:advance()

    return Node:new(
        condition.line,
        {"if", condition, if_body}
    )
end

local Null = {}
Null.__index = Null

function Null:new()
    return setmetatable({}, self)
end

function Null:__eq(other)
    return getmetatable(other) == Null
end

function Null:__ne(other)
    return getmetatable(other) ~= Null
end

function Null:__tostring()
    return "null"
end

local function is_true(t)
    return not (t == false or getmetatable(t) == Null)
end

local Interpreter = {}
Interpreter.__index = Interpreter

function Interpreter:new(path)
    return setmetatable({path = path}, Interpreter)
end

function Interpreter:eval(node, env)
    if node.sxp[1] == "empty" then
        return Null:new()

    elseif node.sxp[1] == "statements" then
        for i = 1, #node.sxp[2] do
            self:eval(node.sxp[2][i], env)
        end
        
        return self:eval(node.sxp[2][#node.sxp[2]], env)

    elseif node.sxp[1] == "number" then
        return tonumber(node.sxp[2])

    elseif node.sxp[1] == "null" then
        return Null:new()

    elseif node.sxp[1] == "true" then
        return true
  
    elseif node.sxp[1] == "false" then
        return false

    elseif node.sxp[1] == "name" then
        local result = env[node.sxp[2]]

        if result == nil then
            return Null:new()
        end

        return result
    
            
    elseif node.sxp[1] == "add" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) + self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "subtract" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) - self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "multiply" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) * self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "divide" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) / self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "eq" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) == self:eval(node.sxp[3], env)
            end,
            node
        )


    elseif node.sxp[1] == "ne" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) ~= self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "lt" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) < self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "gt" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) > self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "le" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) <= self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "ge" then
        return self:eval_operation(
            function ()
                return self:eval(node.sxp[2], env) >= self:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "and" then
        return self:eval_operation(
            function ()
                return is_true(self:eval(node.sxp[2], env)) and is_true(self:eval(node.sxp[3], env))
            end,
            node
        )

    elseif node.sxp[1] == "or" then
        return self:eval_operation(
            function ()
                return is_true(self:eval(node.sxp[2], env)) or iself:eval(node.sxp[3], env)
            end,
            node
        )

    elseif node.sxp[1] == "minus" then
        return self:eval_operation(
            function ()
                return -self:eval(node.sxp[2], env)
            end,
            node
        )
    
    elseif node.sxp[1] == "not" then
        return self:eval_operation(
            function ()
                return not is_true(self:eval(node.sxp[2], env))
            end,
            node
        )

    elseif node.sxp[1] == "if" then
        condition = self:eval(node.sxp[2], env)

        if is_true(condition) then return self:eval(node.sxp[3], env) end

        return Null:new()

    elseif node.sxp[1] == "ifelse" then
        condition = self:eval(node.sxp[2], env)

        if is_true(condition) then return self:eval(node.sxp[3], env) end
        
        return self:eval(node.sxp[4], env)

    elseif node.sxp[1] == "assignment" then
        if node.sxp[2].sxp[1] ~= "name" then
            runtime_error(self.path, node.line)
        end    

        local name = node.sxp[2].sxp[2]
        local value = self:eval(node.sxp[3], env)
                
        env[name] = value

        return value

    else
        error("unknown node type "..node.sxp[1], 2)
    end
end

function Interpreter:eval_operation(func, node)
    if pcall(func) == false then 
        runtime_error(self.path, node.line)
    else
        return func()
    end
end

local global_env = {}

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
    local result = interpreter:eval(tree, global_env)

    print(result)
end