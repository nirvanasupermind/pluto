from src.symbol import Symbol
from src.env import Env
from src.object import Object

def system_exit(args):
    exit()
    
def system_print(args):
    print(args[0], end='')

def system_println(args):
    print(args[0])

null = Symbol('null')
true = Symbol('true')
false = Symbol('false')

object_class = Object()
object_class.env.set('twenty', 20)

function_class = Object()
function_class.env.parent = object_class.env

system_class = Object()
system_class.env.parent = object_class.env
system_class.env.set('exit', Object(system_exit))
system_class.env.set('print', Object(system_print))
system_class.env.set('println', Object(system_println))