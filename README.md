# Besplatno-Compiler

First 2 lines in main:
```auto program = parser.parse("test");
auto std = parser.parse("Std.opl");
```
`test` - name of input OPL file

`Std.opl` - library headers in O language
```
$ ./Besplatno_Compiler 
$ clang a.ll std.ll
$ ./a.out
...
```
## Code generation part
* Inheritance 
  * V tables
* Std


Todo:
* (Optional) Generics
* Example with array
* ...
## Lexical part
* Known bugs:
  * The last line of file contains comment: syntax error

## Syntax part
Todo:
* (Optional) Destructors for ast nodes
* (Optional) void functions
* (Optional) Return constructors to AST (it will make code cleaner)


## Semantic part
Ready
* Cycling inheritance is forbidden
* Redeclaration of classes, method, vars is forbidden
* Overriding members
* Overloading functions and constructors
* Type checking
* Naming checking
* Keywords are in right context
* Generics of multiple types

Todo:
* Forbid cycling var having (e.g. "int" cannot contain "real" that contains "int")
* (Optional) Generics
* Std
  * Arrays
* Opts 
  * Unused vars
  * Unreachable code
    * while/if false/true
  * Constexpr
* (Optional) void functions
* (Optional) strings

## General TODOs:
* More exhaustive example
* Refactor code
* Make doc with language specification 
  * Local vars overwrite global ones (as in C)
  * Real type: .0, 0.0 - correct ones; 0. - incorrect
  * ...
