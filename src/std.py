from src.symbol import Symbol
from src.env import Env
from src.object import Object

def object_constructor(args, this): 
    return Symbol('null')

def string_constructor(args, this): 
    if this != None:
        this.primitive_value = ''

    return Symbol('null')

def string_toString(args, this): 
    if this != None:
        return this

    return Symbol('null')


def function_constructor(args, this): 
    if this != None:
        this.primitive_value = lambda args, this: Symbol('null')

    return Symbol('null')

def system_exit(args, this):
    exit()
    return Symbol('null')
    
def system_print(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0, end='')
    return Symbol('null')
    
def system_println(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0)
    return Symbol('null')

null = Symbol('null')
true = Symbol('true')
false = Symbol('false')

object_class = Object()
object_class.env.set('constructor', Object(object_constructor))

string_class = Object()
string_class.env.set('constructor', Object(string_constructor))
string_class.env.set('toString', Object(string_toString))

function_class = Object()
function_class.env.set('constructor', Object(function_constructor))

system_class = Object()
system_class.env.parent = object_class.env
system_class.env.set('exit', Object(system_exit))
system_class.env.set('print', Object(system_print))
system_class.env.set('println', Object(system_println))