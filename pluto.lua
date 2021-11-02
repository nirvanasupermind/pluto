require('src.lexer')

local dir = (({...})[2] or arg[0]):gsub("[^/]*$", "")

function run(path)
    local file = io.open(dir..path, "rb")
    local input = file:read()
    file:close()

    local tokens = lexer(input)
    
    for i = 1, #tokens do
        local token = tokens[i]

        print(token.type)
    end
end