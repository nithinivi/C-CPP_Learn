

```commandline
gcc -c -o tenth_a.o tenth_a.cpp
objdump -d -S tenth_a.o
```

```text
tenth_a.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <Add>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	89 7d fc             	mov    %edi,-0x4(%rbp)
   b:	89 75 f8             	mov    %esi,-0x8(%rbp)
   e:	8b 55 fc             	mov    -0x4(%rbp),%edx
  11:	8b 45 f8             	mov    -0x8(%rbp),%eax
  14:	01 d0                	add    %edx,%eax
  16:	5d                   	pop    %rbp
  17:	c3                   	retq   

```



```commandline
g++ -o tenth.o tenth.cpp  -fno-stack-protector && ./tenth.o
```
Explanation for     **(((unsigned long)Code) & ~(getpagesize() - 1))**

```Text
00000000000000000001000000000000 getpagesize() 
00000000000000000000111111111111 getpagesize() -1
11111111111111111111000000000000 ~(getpagesize -1 )
11101111010100000001111010110000 ((unsigned long)Code)
11101111010100000001000000000000 (((unsigned long)Code) & ~(getpagesize() - 1))
```

- fno-stack-protector 
   
   Its used for disabling canaries protection of gcc. or while on runtime stack smashing detection can result in core dump 


### Further Reading 
    - https://valgrind.org/
