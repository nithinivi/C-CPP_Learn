#include<stdio.h>
#include<dlfcn.h>

typedef int(*BIN_FUNCTION)(int, int);

int main(int argc, char *argv[])
{
    void *handle = dlopen("libArith.so", RTLD_LAZY);
    if (handle == 0) {
        printf("Faild to load the program \n");
        return 0;
    }

    BIN_FUNCTION bn = (BIN_FUNCTION)dlsym(handle, "Add");
    if (bn==0) {
        printf("Faild to load the function \n");
        return 0;
    }
    int nc = (*bn)(10,10);
    printf("Value is %d \n", nc);
    dlclose(handle);

    return 0;
}
