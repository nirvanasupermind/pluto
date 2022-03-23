# Pluto
Work-in-progress C++ interpreter for the Pluto programming language.

Once completed, Pluto will be a lightweight, dynamic programming language with multithreading support.

# Working example
```
class Vec {
    def constructor(x, y) {
        self.x = x;
        self.y = y;
    }

    def magSquared() {
        return (self.x * self.x) + (self.y * self.y);
    }
}

var vec = Vec(2, 3);

System.print(vec.magSquared()); # 13
```