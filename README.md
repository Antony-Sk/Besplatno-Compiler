# Besplatno-Compiler

Then build project and run it:
```./Besplatno-Compiler
> 123
Integer Literal: 123 Line: 0 Pos: 0 3
Delimiter: '
' Line: 0 Pos: 3 4
> 
```
Or pass your program through a pipe:
```
$ cat examples/programs/Inheritance.opl | ./cmake-build-debug/Besplatno_Compiler 
Class Line: 0 Pos: 0 5
Delimiter: ' ' Line: 0 Pos: 5 6
Identifier: A Line: 0 Pos: 6 7
Delimiter: ' ' Line: 0 Pos: 7 8
Assignment Line: 0 Pos: 8 10
Delimiter: '
' Line: 0 Pos: 10 11
Delimiter: '    ' Line: 1 Pos: 0 4
Variable Declaration Line: 1 Pos: 4 7
Delimiter: ' ' Line: 1 Pos: 7 8
Identifier: a Line: 1 Pos: 8 9
Delimiter: ' ' Line: 1 Pos: 9 10
Delimiter: ':' Line: 1 Pos: 10 11
Delimiter: ' ' Line: 1 Pos: 11 12
Boolean Line: 1 Pos: 12 19
...
```

## Lexical part

Todo on lexical part:
* The rest of tokens
* 3..1:
  * I did that 1. is not valid real but .1 and 1.1 are valid ones

## Syntax part

Todo:
* Inheritance
* Generics
* []