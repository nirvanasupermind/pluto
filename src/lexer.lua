local WHITESPACE = " \n\t"

function lexer(input)
    if input == nil then input = "" end

    local index = 1
    local tokens = {}

    while index <= #input do
        local char = input:sub(index, index)

        if string.find(WHITESPACE, char, 1, true) then
            index = index + 1
        
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
            print("error: illegal character '"..char.."'")
            os.exit()
        end
    end

    return tokens
end