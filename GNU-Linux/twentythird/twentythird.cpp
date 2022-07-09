///////////////////////////////////////////////////////////////////////////////
//                             Memory Mapped file                            //
///////////////////////////////////////////////////////////////////////////////

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

void populateValues() {
    unlink("test.tmp");
    int fd = open("test.tmp", O_RDWR | O_CREAT);
    if (fd == -1) {
        fprintf(stdout, "failed to open test.bin %d", fd);
        exit(0);
    }
    int val;
    for (val = 0; val < 20; val++) {
        write(fd, &val, 4);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    populateValues();

    int fd;
    if ((fd = open("test.tmp", O_RDWR)) == -1) {
        fprintf(stdout, "failed to open test.bin %d", fd);
        exit(0);
    }

    // map the entire content of the file to pointer
    int *mapped_values = (int *)mmap(0, 20 * sizeof(int),
                                     PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int val;
    for (val = 0; val < 20; val++)
        mapped_values[val] *= 2;

    msync((void *)mapped_values, 20 * sizeof(int), MS_ASYNC);
    munmap((void *)mapped_values, 20 * sizeof(int));
    lseek(fd, 0, 0);
    for (size_t i = 0; i < 20; i++) {
        read(fd, &val, sizeof(int));
        printf("%d\n", val);
    }

    close(fd);
    unlink("test.tmp");

    return 0;
}
