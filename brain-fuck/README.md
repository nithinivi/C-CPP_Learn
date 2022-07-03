# Brainfuck

Brainfuck is a weird looking programming language and keeps every promise its name makes. Here is “Hello, World!” in Brainfuck:

```
++++++++[>++++[>++>+++>+++>+<<
<<-]>+>+>->>+[<]<-]>>.>---.+++
++++..+++.>>.<-.<.+++.------.-
-------.>>+.>++.
```

The componets of the Languages are as follows. 
This is largely influenced by this [blog](https://thorstenball.com/blog/2017/01/04/a-virtual-brainfuck-machine-in-go/)

### Memory

The machine has 30000 memory cells, that can each hold an integer value from 0 to 255 and are initialized to 0 by default. Each cell is addressable by a zero based index, giving us a range of 0 to 29999 as possible indexes.

### Data pointer
It “points” to a memory cell, by holding the value of the cell’s index. E.g.: if the value of the data pointer is 3, it points to the fourth memory cell.

### Code
The program that’s executed by the machine. It’s made up of single instructions, which we’ll get to in a short while.

### Instruction pointer

It points to the instruction in the code that’s to be executed next. E.g.: if the code is ++-++ and the instruction pointer has the value 2 then the next instruction to be executed is -.

### Input and output streams
Just like STDIN and STDOUT in Unix systems, these are normally connected to the keyboard and the screen and are used for printing and reading characters.

### CPU
It fetches the next instruction from the code and executes it, manipulating the data pointer, instruction pointer, a memory cell or the input/output streams accordingly.
