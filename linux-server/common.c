#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

const char *program_name;
int verbose;

void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL)
        abort();
    else
        return ptr;
}

void *xrealloc(void *ptr, size_t size) {
    ptr = realloc(ptr, size);
    if (ptr == NULL)
        abort();
    else
        return ptr;
}

// duplicate of the string with error management
char *xstrdup(const char *s) {
    char *copy = strdup(s);
    if (copy == NULL)
        abort();
    else
        return copy;
}

// managing error iwith error operation
void system_error(const char *operation) { error(operation, strerror(errno)); }

void error(const char *cause, const char *message) {
    fprintf(stderr, "%s error : (%s) %s", program_name, cause, message);
    exit(1);
}

/* Return the directory containing the running program’s executable.
The return value is a memory buffer that the caller must deallocate
using free. This function calls abort on failure. */
char *get_self_executable_directory() {
    int rval;
    char link_target[1024];
    char *last_slash;
    size_t result_length;
    char *result;

    rval = readlink("/proc/self/exe", link_target, sizeof(link_target));
    if (rval == -1)
        abort();
    else
        link_target[rval] = '\0';

    // find the last occurence of the  /
    last_slash = strrchr(link_target, '/');

    if (last_slash == NULL || last_slash == link_target)
        abort();

    // copies until the last slash
    result_length = last_slash - link_target;
    result = (char *)xmalloc(result_length + 1);

    strncpy(result, link_target, result_length);
    result[result_length] = '\0';
    return result;
}
