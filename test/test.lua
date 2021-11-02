local dir = (({...})[2] or arg[0]):gsub("[^/]*$", "")
dofile(dir.."../pluto.lua")

run("./test.pluto")