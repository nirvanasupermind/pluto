from src.env import Env
from src.std import *

global_env = Env(is_global_env=True)
global_env.set('null', null)
global_env.set('true', true)
global_env.set('false', false)

global_env.set('Object', object_class)
global_env.set('Class', class_class)
global_env.set('String', string_class)
global_env.set('List', list_class)
global_env.set('Function', function_class)

global_env.set('System', system_class)