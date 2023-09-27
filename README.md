# Besplatno-Compiler

Then build project and run it:
```./Besplatno-Compiler
> 123
Saw an integer: 123
Token: 4 0
> 
```
Or pass your program through a pipe:
```
$ cat examples/programs/Fibonacci.opl | ./cmake-build-debug/Besplatno_Compiler 
Token: 1 0
Saw an identifier: Integer
Token: 1 0
Saw an identifier: Integer
Token: 4 0
Saw an integer: 1
Token: 4 0
Saw an integer: 1
Token: 4 0
Saw an integer: 1
Token: 4 0
Saw an integer: 5
Token: 4 0
Saw an integer: 120
```

## Lexical part
To generate lex.yy.cpp:

```flex -o lex.l.cpp lex.l```

Todo on lexical part:
* The rest of tokens
* Change flex -> flex++
* Output format of LexicalAnalyzer class
    * Implement nextToken()
    * Or make a function that returns list of all tokens
* Add loc and position in code to token