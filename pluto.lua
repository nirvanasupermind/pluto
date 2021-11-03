local WHITESPACE = " \n\t"
local DIGITS = "0123456789"
local PATH = (({...})[2] or arg[0]):gsub("[^/]*$", "")

-- utility function
function contains(tbl, item)
    for key, value in pairs(tbl) do
        if value == item then return key end
    end
    return false
end

-- utility function for debugging
function tprint (t, s)
    for k, v in pairs(t) do
        local kfmt = '["' .. tostring(k) ..'"]'
        if type(k) ~= 'string' then
            kfmt = '[' .. k .. ']'
        end
        local vfmt = '"'.. tostring(v) ..'"'
        if type(v) == 'table' then
            tprint(v, (s or '')..kfmt)
        else
            if type(v) ~= 'string' then
                vfmt = tostring(v)
            end
            print(type(t)..(s or '')..kfmt..' = '..vfmt)
        end
    end
end


function lexical_error(path, line)
    print("pluto: "..path..":"..line..": ".."lexical error")
    os.exit()
end

function syntax_error(path, line)
    print("pluto: "..path..":"..line..": ".."syntax error")
    os.exit()
end

function lexer(path, input)
    if input == nil then input = "" end

    local index = 1
    local line = 1
    local tokens = {}

    while index <= #input do
        local char = input:sub(index, index)

        if string.find(WHITESPACE, char, 1, true) then
            if char == "\n" then line = line + 1 end
            index = index + 1

        elseif string.find(DIGITS, char, 1, true) then
            local value = ""
            local dot_count = 0

            while index <= #input 
                  and string.find(DIGITS..".", char, 1, true) do
                if char == "." then
                    dot_count = dot_count + 1
                    if dot_count > 1 then break end
                end

                value = value..char
                index = index + 1
                char = input:sub(index, index)
            end

            tokens[#tokens + 1] = {
                line = line, 
                type = "num", 
                value = value
            }

        elseif char == "+" then
            index = index + 1
            tokens[#tokens + 1] = {
                line = line, 
                type = "plus"
            }

        elseif char == "-" then
            index = index + 1
            tokens[#tokens + 1] = {
                line = line, 
                type = "minus"
            }

        elseif char == "*" then
            index = index + 1
            tokens[#tokens + 1] = {
                line = line, 
                type = "multiply"
            }

        elseif char == "/" then
            index = index + 1
            tokens[#tokens + 1] = {
                line = line, 
                type = "divide"
            }

        elseif char == "(" then
            index = index + 1
            tokens[#tokens + 1] = {
                line = line, 
                type = "lparen"
            }

        elseif char == ")" then
            index = index + 1
            tokens[#tokens + 1] = {
                line = line, 
                type = "rparen"
            }

        else
            lexical_error(path, line)
        end
    end

    tokens[#tokens + 1] = { 
        line = line, 
        type = "eof"
    }

    return tokens
end

function parser(path, tokens)
    index = 1

    function expr()
        return additive_expr()
    end

    function additive_expr()
        result = multiplicative_expr()

        while tokens[index].type ~= "eof" 
              and contains({"plus", "minus"}, tokens[index].type) do
            if tokens[index].type == "plus" then
                index = index + 1
                result = {
                    line = result.line, 
                    type = "plus", 
                    args = {result, multiplicative_expr()}
                }
            else
                index = index + 1
                result = {
                    line = result.line, 
                    type = "minus", 
                    args = {result, multiplicative_expr()}
                }
            end
        end 

        return result
    end

    function multiplicative_expr()
        result = leaf_expr()

        while tokens[index].type ~= "eof" 
              and contains({"multiply", "divide"}, tokens[index].type) do
            if tokens[index].type == "multiply" then
                index = index + 1
                result = {
                    line = result.line, 
                    type = "multiply", 
                    args = {result, leaf_expr()}
                }
            else
                index = index + 1
                result = {
                    line = result.line, 
                    type = "divide", 
                    args = {result, leaf_expr()}
                }
            end
        end 

        return result
    end

    function leaf_expr()
        token = tokens[index]

        if token.type == "num" then
            index = index + 1
            return {
                line = token.line,
                type = "num",
                value = token.value
            }

        elseif token.type == "lparen" then
            index = index + 1

            exp = expr()

            if tokens[index].type ~= "rparen" then
                syntax_error(path, tokens[index].line)
            end

            return expr()
        else
            syntax_error(path, tokens[index].line)
        end
    end

    if tokens[index].type == "eof" then
        return {
            line = tokens[index].line,
            type = "empty"
        }
    end

    local result = expr()

    if tokens[index].type ~= "eof" then 
        syntax_error(path, tokens[index].line) 
    end

    return result
end

if #arg == 1 then
    local path = arg[1]
    local file = io.open(PATH..path, "rb")
    local input = file:read("*a")
    file:close()

    local tokens = lexer(path, input)
    local tree = parser(path, tokens)

    tprint(tree)
end