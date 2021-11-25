import string
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
object_class.set('constructor', Object(object_constructor))

class_class = Object()
# class_class.klass = class_class
object_class.klass = class_class

string_class = Object()
string_class.klass = class_class
string_class.base = object_class
string_class.set('constructor', Object(string_constructor))
string_class.set('toString', Object(string_toString))

function_class = Object()
function_class.klass = class_class
function_class.base = object_class
function_class.set('constructor', Object(function_constructor))

system_class = Object()
system_class.klass = class_class
system_class.base = object_class
system_class.set('exit', Object(system_exit))
system_class.set('print', Object(system_print))
system_class.set('println', Object(system_println))