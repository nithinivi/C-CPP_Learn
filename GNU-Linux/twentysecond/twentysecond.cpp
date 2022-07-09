///////////////////////////////////////////////////////////////////////////////
//                             interrupt handling
//                           press ctrl+c 3 times
///////////////////////////////////////////////////////////////////////////////
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void interrupt_handler(int cause) {
    static int test = 0;
    test++;

// inactive preprocessor at this part
#if 0 // make this 1 to compile #if part
    if(test==3)
      exit(0);
    else
      print("Press Ctrl+c %d times\n", 3 - test);
#else
    if (test == 2)
        // reset to default behaviour
        signal(SIGINT, SIG_DFL);
    else
        printf("Press Ctrl+c %d times\n", 3 - test);
#endif
    return;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, interrupt_handler);
    while (true) {
    }

    return 0;
}
