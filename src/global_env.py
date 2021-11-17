from src.symbol import Symbol
from src.env import Env

global_env = Env(is_global_env=True)
global_env.set('null', Symbol('null'))
global_env.set('true', Symbol('true'))
global_env.set('false', Symbol('false'))