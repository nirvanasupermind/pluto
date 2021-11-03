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

            while index <= #input and string.find(DIGITS..".", char, 1, true) do
                if char == "." then
                    dot_count = dot_count + 1
                    if dot_count > 1 then break end
                end

                value = value..char
                index = index + 1
                char = input:sub(index, index)
            end

            tokens[#tokens + 1] = {line = line, type = "num", value = value}

        elseif char == "+" then
            index = index + 1
            tokens[#tokens + 1] = {line = line, type = "plus"}

        elseif char == "-" then
            index = index + 1
            tokens[#tokens + 1] = {line = line, type = "minus"}

        elseif char == "*" then
            index = index + 1
            tokens[#tokens + 1] = {line = line, type = "multiply"}

        elseif char == "/" then
            index = index + 1
            tokens[#tokens + 1] = {line = line, type = "divide"}

        elseif char == "(" then
            index = index + 1
            tokens[#tokens + 1] = {line = line, type = "lparen"}

        elseif char == ")" then
            index = index + 1
            tokens[#tokens + 1] = {line = line, type = "rparen"}

        else
            lexical_error(path, line)
        end
    end

    return tokens
end

if #arg == 1 then
    local path = arg[1]
    local file = io.open(PATH..path, "rb")
    local input = file:read("*a")
    file:close()

    local tokens = lexer(path, input)
    
    for i = 1, #tokens do
        local token = tokens[i]

        print(token.type)
    end
end