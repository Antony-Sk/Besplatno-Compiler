# Besplatno-Compiler

Pass your program through a pipe:
```
$ cat examples/programs/Inheritance.opl | ./Besplatno_Compiler 
Program
-Class : Main
--Member decl
---Constructor
----Args
----Statements
-----Statement
------Var decl : x
-------Expression with value : 
--------Method 'B' call with args:
---------Expressions
----------Expression with value : 1
----------Expression with value : 2
...
```

## Lexical part
Todo on lexical part:
* Known bugs:
  * The last line of file contains comment: syntax error

## Syntax part
Todo
* Check on bugs
* Destructors for ast nodes
* Add position of structs in code in ast nodes
* void functions

## Semantic part
Ready
* Cycling inheritance is forbidden
* Redeclaration of classes, method, vars is forbidden
* Overriding members
* Overloading functions and constructors
* Type checking
* Naming checking
* Keywords are in right context

Todo:
* Forbid cycling var having (e.g. "int" cannot contain "real" that contains "int")
* Generics
* Std
* Opts 
  * Unused vars
  * Unreachable code
  * Constexpr
* void functions

## General TODOs:
* More exhaustive example
* Refactor code
* Make doc with language specification 
  * Local vars overwrite global ones (as in C)
  * Real type: .0, 0.0 - correct ones; 0. - incorrect
  * ...
