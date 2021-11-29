import numpy as np
import random
from datetime import datetime
from src.char import Char
from src.symbol import Symbol
from src.env import Env
from src.object import java_string_hashcode, Object

class IllegalArgument(BaseException): pass
class NoThis(BaseException): pass
class IndexOutOfRange(BaseException): pass
    
def object_constructor(args, this): 
    if this == None:
        raise NoThis()

def object_hashCode(args, this): 
    if this == None:
        raise NoThis()
    
    return this.hashcode()

def object_toString(args, this): 
    if this == None:
        raise NoThis()
    
    return f'{this}'

def string_constructor(args, this):
    if this == None:
        raise NoThis()

    if len(args) > 0 and not (isinstance(args[0], Object) and isinstance(args[0].primitive_value, str)):
        raise IllegalArgument()

    this.primitive_value = args[0].primitive_value if len(args) > 0 else ''

    return Symbol('null')
 
def string_charAt(args, this):
    if this == None:
        raise NoThis()
    
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, np.int32):
        raise IllegalArgument()

    if arg0 >= len(this.primitive_value) or arg0 < 0:
        raise IndexOutOfRange()

    return Char(ord(this.primitive_value[arg0]))


def string_concat(args, this):
    if this == None:
        raise NoThis()
    
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not (isinstance(arg0, Object) and isinstance(arg0.primitive_value, str)):
        raise IllegalArgument()

    return Object(this.primitive_value + arg0.primitive_value, string_class)

   
def string_hashCode(args, this): 
    if this == None:
        raise NoThis()
    
    return np.int32(java_string_hashcode(this.primitive_value))

def string_indexOf(args, this):
    if this == None:
        raise NoThis()
    
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not (isinstance(arg0, Object) and isinstance(arg0.primitive_value, str)):
        raise IllegalArgument()

    try:
        return np.int32(this.primitive_value.index(arg0.primitive_value))
    except ValueError:
        return np.int32(-1)

def string_lastIndexOf(args, this):
    if this == None:
        raise NoThis()
    
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not (isinstance(arg0, Object) and isinstance(arg0.primitive_value, str)):
        raise IllegalArgument()

    try:
        return np.int32(this.primitive_value.rindex(arg0.primitive_value))
    except ValueError:
        return np.int32(-1)

def string_length(args, this):
    if this == None:
        raise NoThis()

    return np.int32(len(this.primitive_value))

def string_toString(args, this): 
    if this == None:
        raise NoThis()

    return this
    
def string_valueOf(args, this): 
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    return Object(str(arg0), string_class)

def list_constructor(args, this): 
    if this == None:
        raise NoThis()
    
    if len(args) > 0 and not (isinstance(args[0], Object) and isinstance(args[0].primitive_value, list)):
        raise IllegalArgument()

    this.primitive_value = args[0].primitive_value if len(args) > 0 else []

    return Symbol('null')

def list_add(args, this): 
    if this == None:
        raise NoThis()

    arg0 = args[0] if len(args) > 0 else Symbol('null')

    this.primitive_value.append(arg0)

    return Symbol('null')

def list_clear(args, this): 
    if this == None:
        raise NoThis()

    this.primitive_value.clear()

    return Symbol('null')

def list_concat(args, this): 
    if this == None:
        raise NoThis()

    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not (isinstance(args[0], Object) and isinstance(args[0].primitive_value, list)):
        raise IllegalArgument()

    return Object(this.primitive_value + arg0.primitive_value, list_class)

def list_first(args, this): 
    if this == None:
        raise NoThis()

    if len(this.primitive_value) == 0:
        raise IllegalArgument()

    return this.primitive_value[0]

def list_get(args, this): 
    if this == None:
        raise NoThis()

    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, np.int32):
        raise IllegalArgument()

    if arg0 >= len(this.primitive_value) or arg0 < 0:
        raise IndexOutOfRange()

    return this.primitive_value[arg0]

def list_indexOf(args, this): 
    if this == None:
        raise NoThis()
        
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    try:
        return np.int32(this.primitive_value.index(arg0))
    except ValueError:
        return np.int32(-1)

def list_last(args, this): 
    if this == None:
        raise NoThis()

    if len(this.primitive_value) == 0:
        raise IllegalArgument()

    return this.primitive_value[-1]

def list_lastIndexOf(args, this): 
    if this == None:
        raise NoThis()

    arg0 = args[0] if len(args) > 0 else Symbol('null')

    try:
        return np.int32(this.primitive_value.rindex(arg0))
    except ValueError:
        return np.int32(-1)

def list_remove(args, this): 
    if this == None:
        raise NoThis()

    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, np.int32):
        raise IllegalArgument()

    if arg0 >= len(this.primitive_value) or arg0 < 0:
        raise IndexOutOfRange()

    result = this.primitive_value[arg0]

    del this.primitive_value[arg0]

    return result

def list_set(args, this): 
    if this == None:
        raise NoThis()

    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, np.int32):
        raise IllegalArgument()
    
    if arg0 >= len(this.primitive_value) or arg0 < 0:
        raise IndexOutOfRange()

    arg1 = args[1] if len(args) > 1 else Symbol('null')

    this.primitive_value[arg0] = arg1

    return arg1

def list_size(args, this): 
    if this == None:
        raise NoThis()

    return np.int32(len(this.primitive_value))

def list_toString(args, this): 
    if this == None:
        raise NoThis()

    return f'[{", ".join(map(str, this.primitive_value))}]'

def function_constructor(args, this): 
    if this != None:
        this.primitive_value = lambda args, this: Symbol('null')

    raise IllegalArgument()

def math_abs(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.abs(arg0)

def math_acos(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.arccos(arg0)

def math_asin(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.arcsin(arg0)

def math_atan(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.arctan(arg0)

def math_ceil(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.ceil(arg0)

def math_cos(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.cos(arg0)

def math_exp(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.exp(arg0)

def math_floor(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.floor(arg0)
    
def math_log(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.log(arg0)

def math_max(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()

    arg1 = args[1] if len(args) > 1 else Symbol('null')

    if not isinstance(arg1, (np.int32, float)):
        raise IllegalArgument()

    return arg0 if arg0 > arg1 else arg1

def math_min(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()

    arg1 = args[1] if len(args) > 1 else Symbol('null')

    if not isinstance(arg1, (np.int32, float)):
        raise IllegalArgument()

    return arg0 if arg0 < arg1 else arg1

def math_pow(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()

    arg1 = args[1] if len(args) > 0 else Symbol('null')

    if not isinstance(arg1, (np.int32, float)):
        raise IllegalArgument()

    return arg0 ** arg1

def math_random(args, this):
    return np.random.random()

def math_round(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.round(arg0)

def math_sign(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.sign(arg0)

def math_sin(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.sin(arg0)

def math_sqrt(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.sqrt(arg0)

def math_tan(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    if not isinstance(arg0, (np.int32, float)):
        raise IllegalArgument()
    
    return np.tan(arg0)

def system_exit(args, this):
    exit()

def system_millis(args, this):
    return np.int32((datetime.utcnow() - datetime(1970, 1, 1)).total_seconds() * 1000)
    
def system_print(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0, end='')
    
def system_println(args, this):
    arg0 = args[0] if len(args) > 0 else Symbol('null')

    print(arg0)

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

math_class = Object()
math_class.klass = class_class
math_class.base = object_class

object_class.set('constructor', Object(object_constructor, function_class))
object_class.set('hashCode', Object(object_hashCode, function_class))
object_class.set('toString', Object(object_toString, function_class))

string_class.set('constructor', Object(string_constructor, function_class))
string_class.set('charAt', Object(string_charAt, function_class))
string_class.set('concat', Object(string_concat, function_class))
string_class.set('hashCode', Object(string_hashCode, function_class))
string_class.set('indexOf', Object(string_indexOf, function_class))
string_class.set('lastIndexOf', Object(string_lastIndexOf, function_class))
string_class.set('length', Object(string_length, function_class))
string_class.set('toString', Object(string_toString, function_class))
string_class.set('valueOf', Object(string_valueOf, function_class))

list_class.set('constructor', Object(list_constructor, function_class))
list_class.set('add', Object(list_add, function_class))
list_class.set('clear', Object(list_clear, function_class))
list_class.set('concat', Object(list_concat, function_class))
list_class.set('first', Object(list_first, function_class))
list_class.set('get', Object(list_get, function_class))
list_class.set('indexOf', Object(list_indexOf, function_class))
list_class.set('last', Object(list_last, function_class))
list_class.set('lastIndexOf', Object(list_lastIndexOf, function_class))
list_class.set('remove', Object(list_remove, function_class))
list_class.set('set', Object(list_set, function_class))
list_class.set('size', Object(list_size, function_class))
list_class.set('toString', Object(list_toString, function_class))

function_class.set('constructor', Object(function_constructor, function_class))

math_class.set('E', np.e)
math_class.set('PI', np.pi)
math_class.set('SQRT2', np.sqrt(2.0))
math_class.set('abs', Object(math_abs, function_class))
math_class.set('acos', Object(math_acos, function_class))
math_class.set('asin', Object(math_asin, function_class))
math_class.set('atan', Object(math_atan, function_class))
math_class.set('ceil', Object(math_ceil, function_class))
math_class.set('cos', Object(math_cos, function_class))
math_class.set('exp', Object(math_exp, function_class))
math_class.set('floor', Object(math_floor, function_class))
math_class.set('log', Object(math_log, function_class))
math_class.set('max', Object(math_max, function_class))
math_class.set('min', Object(math_min, function_class))
math_class.set('pow', Object(math_pow, function_class))
math_class.set('sin', Object(math_sin, function_class))
math_class.set('sqrt', Object(math_sqrt, function_class))
math_class.set('tan', Object(math_tan, function_class))

system_class.set('exit', Object(system_exit, function_class))
system_class.set('millis', Object(system_millis, function_class))
system_class.set('print', Object(system_print, function_class))
system_class.set('println', Object(system_println, function_class))