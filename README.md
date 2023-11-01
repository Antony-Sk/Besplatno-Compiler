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
* More example maybe

## Semantic part
Ready
* Cycling inheritance is forbidden
* Redeclaration of class is forbidden
* Overriding members
Todo:
* Type checking on functions
* Generics