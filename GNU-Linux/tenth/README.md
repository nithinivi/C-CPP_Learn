```
gcc -c -o tenth_a.o tenth_a.cpp
objdump -d -S tenth_a.o
```


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
