# Besplatno-Compiler

Pass your program through a pipe:
```
$ cat examples/programs/Inheritance.opl | ./cmake-build-debug/Besplatno_Compiler 
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
* Comments are buggy, test it

## Syntax part
Todo
* Check on bugs
* More example maybe