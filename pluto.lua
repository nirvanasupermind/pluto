#!/usr/bin/env lua

local WHITESPACE = " \n\t"
local DIGITS = "0123456789"
local PATH = (({...})[2] or arg[0]):gsub("[^/]*$", "")

function lexical_error(path, line)
    print("pluto: "..path..":"..line..": ".."lexical error")
    os.exit()
end

function syntax_error(path, line)
    print("pluto: "..path..":"..line..": ".."syntax error")
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
        index = 0,
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
    tokens = {}

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
    value = ""
    decimal_point_count = 0
    
    while string.find(DIGITS..".", self:current(), 1, true) do
        if self:current() == "." then
            decimal_point_count = decimal_point_count + 1
            if decimal_point_count > 1 then break end
        end

        value = value..self:current()
        self:advance()
    end

    return Token:new(self.line, "NUMBER", value)
end

if #arg == 1 then
    local path = arg[1]
    local file = io.open(PATH..path, "rb")
    local text = file:read("*a")
    file:close()

    local lexer = Lexer:new(path, text)
    local tokens = lexer:get_tokens()

    -- local value = interpreter(path, tree)

    for i = 1, #tokens do
        print(tokens[i])
    end
end