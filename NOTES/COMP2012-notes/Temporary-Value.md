# Temporary Objects

### Dynamic Object

+ **Dynamic objects** are managed by the heap. 
+ If you lose all pointers to a dynamic object, you lose the object — resulting in a memory leak.

### Temporary objects/values

Another kind of **unnamed objects/values** created automatically on **the stack** during:

+ {TO1} const reference initialization
+ {TO2} argument passing (e.g., type conversion)
+ {TO3} function **returned value** (by copying)
+ {TO4} evaluation of expressions (e.g., result of sub-expressions)

> 1. **managed by the stack.**
> 2. **destructed automatically by the stack** 

