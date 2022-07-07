#include <bitset>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

char addfunc[] = "\xf3\x0f\x1e\xfa\x55\x48\x89"
                 "\xe5\x89\x7d\xfc\x89\x75\xf8\x8b\x55\xfc\x8b"
                 "\x45\xf8\x01\xd0\x5d\xc3";

int main(int argc, char *argv[]) {

    char *Code = (char *)malloc(100);


    
    // index of the page 
    unsigned long page = ((unsigned long)Code) & ~(getpagesize() - 1);

    if (mprotect((char *)page, getpagesize(),
                 PROT_READ | PROT_WRITE | PROT_EXEC)) {
        perror("mprotect failed");
        exit(errno);
    }

    // copy the code from addfunc to code
    memcpy(Code, addfunc, sizeof(addfunc));

    // Casting the code to function pointer
    int (*AddFunc)(int, int) = (int (*)(int, int))((void *)Code);
    int retval = AddFunc(10, 6);
    printf("%d\n", retval);

    if (mprotect((char *)page, getpagesize(), PROT_READ | PROT_WRITE)) {
        perror("mprotect failed");
        exit(errno);
    }
    
    //----------Free the heap allocated memory

    free(Code);
    return 0;
}
