from src.symbol import Symbol
from src.env import Env
from src.object import Object

    
def system_exit(args):
    exit()
    return Symbol('null')
    
def system_print(args):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0, end='')
    return Symbol('null')

def system_println(args):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0)
    return Symbol('null')

null = Symbol('null')
true = Symbol('true')
false = Symbol('false')

object_class = Object()

function_class = Object()

system_class = Object()
system_class.env.parent = object_class.env
system_class.env.set('exit', Object(system_exit))
system_class.env.set('print', Object(system_print))
system_class.env.set('println', Object(system_println))