local WHITESPACE = " \n\t"
local DIGITS = "0123456789"

function lex(file, input)
    local index = 1
    local tokens = {}

    while index < #input + 1 do
        char = input:sub(index, index)

        if string.find(WHITESPACE, char, 1, true) then
            index = index + 1
        elseif string.find(DIGITS, char, 1, true) then
            value = ""
            dot_count = 0

            while index < #input + 1 and string.find(DIGITS .. ".", char) do
                if char == "." then
                    if dot_count >= 1 then break end
                    dot_count = dot_count + 1
                end

                value = value .. char
                index = index + 1
                char = input:sub(index, index)
            end
        
            tokens[#tokens + 1] = {type = "num", value = value}
        elseif char == "+" then
            index = index + 1
            tokens[#tokens + 1] = {type = "plus"}
        elseif char == "-" then
            index = index + 1
            tokens[#tokens + 1] = {type = "minus"}
        elseif char == "*" then
            index = index + 1
            tokens[#tokens + 1] = {type = "multiply"}
        elseif char == "/" then
            index = index + 1
            tokens[#tokens + 1] = {type = "divide"}
        elseif char == "(" then
            index = index + 1
            tokens[#tokens + 1] = {type = "lparen"}
        elseif char == ")" then
            index = index + 1
            tokens[#tokens + 1] = {type = "rparen"}
        else
            print(file .. ": " .. "error: lexical error")
            os.exit()
        end
    end

    tokens[#tokens + 1] = {type = "eof"}

    return tokens
end

-- https://stackoverflow.com/questions/11201262/how-to-read-data-from-a-file-in-lua
function lines_from(file)
    lines = {}
    for line in io.lines(file) do 
      lines[#lines + 1] = line
    end
    return lines
end

function run(file)
    local input = table.concat(lines_from(file), "\n")
    local tokens = lex(file, input)

    print("TOKENS:")

    for i = 1, #tokens do
        if tokens[i].value then
            print(tokens[i].type .. ":" .. tokens[i].value)
        else
            print(tokens[i].type)
        end
    end
end