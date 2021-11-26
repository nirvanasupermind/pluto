import numpy as np
from src.char import Char
from src.symbol import Symbol
from src.env import Env
from src.object import Object
   
def raise_error():
    raise SystemExit()
    
def object_constructor(args, this): 
    if this == None:
        raise_error()

def string_constructor(args, this): 
    if this == None:
        raise_error()

    this.primitive_value = ''

    return Symbol('null')

def string_toString(args, this): 
    if this == None:
        raise_error()

    return this
    
def string_eq(args, this):
    if this == None:
        raise_error()

    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if this.primitive_value == arg0.primitive_value:
        return Symbol('true')
    else:
        return Symbol('false')
    
def string_length(args, this):
    if this == None:
        raise_error()

    return np.int32(len(this.primitive_value))
        
def string_charAt(args, this):
    if this == None:
        raise_error()
    
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, np.int32):
        raise_error()

    if arg0 >= len(this.primitive_value) or arg0 < -len(this.primitive_value):
        raise_error()

    return Char(ord(this.primitive_value[arg0]))
        
def list_constructor(args, this): 
    if this != None:
        this.primitive_value = []

    return Symbol('null')

def list_toString(args, this): 
    if this != None:
        return f'[{", ".join(this.primitive_value)}]'

    raise_error()

def function_constructor(args, this): 
    if this != None:
        this.primitive_value = lambda args, this: Symbol('null')

    raise_error()

def system_exit(args, this):
    exit()
    
def system_print(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0, end='')
    raise_error()
    
def system_println(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0)
    raise_error()

null = Symbol('null')
true = Symbol('true')
false = Symbol('false')

object_class = Object()
class_class = Object()
object_class.klass = class_class

string_class = Object()
string_class.klass = class_class
string_class.base = object_class

list_class = Object()
list_class.klass = class_class
list_class.base = object_class

function_class = Object()
function_class.klass = class_class
function_class.base = object_class

system_class = Object()
system_class.klass = class_class
system_class.base = object_class

object_class.set('constructor', Object(object_constructor, function_class))

string_class.set('constructor', Object(string_constructor, function_class))
string_class.set('toString', Object(string_toString, function_class))
string_class.set('length', Object(string_length, function_class))
string_class.set('charAt', Object(string_charAt, function_class))

list_class.set('constructor', Object(list_constructor, function_class))
list_class.set('toString', Object(list_toString, function_class))

function_class.set('constructor', Object(function_constructor, function_class))

system_class.set('exit', Object(system_exit, function_class))
system_class.set('print', Object(system_print, function_class))
system_class.set('println', Object(system_println, function_class))