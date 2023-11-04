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
* Destructors for ast nodes!!!
* Add position of structs in code in ast nodes

## Semantic part
Ready
* Cycling inheritance is forbidden
* Redeclaration of class is forbidden
* Overriding members
* Type checking
* Naming checking
Todo:
* Recursive var having (e.g. "int" cannot contain "int")
* Generics !!!!!!! GENERICS !!!!!
* Std

## General TODOs:
* More exhaustive example
* Refactor code
  * replace std::holds_alternative by std::visit where it is possible
* Make doc with language specification 
  * Local vars overwrite global ones (as in C)
  * Real type: .0, 0.0 - correct ones; 0. - incorrect
  * ...