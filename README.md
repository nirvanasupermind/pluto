# Pluto
Work-in-progress C++ interpreter for the Pluto programming language.

Once completed, Pluto will be a lightweight, dynamic programming language with multithreading support.

# Changelog

# Running example
```
def factorial(x) {
    if(x == 0.0) {
        return 1.0;
    } else {
        return x * factorial(x - 1.0);
    }
}

Pluto.print(factorial(5.0));
```
