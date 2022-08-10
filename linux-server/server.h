#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/types.h>

/* Symbols defined in common.c ***********************************************/

/* name of the program *******************************************************/
extern const char *program_name;

/* if nonzero print verbose messages  ****************************************/
extern int verbose;

/* Like malloc, expects abort the program if allocation fails ****************/
extern void *xmalloc(size_t size);

/* Like realloc, expects aborts the program if allocation fails
 * ****************/
extern void *xrealloc(void *ptr, size_t size);

/* Like strdup, expects aborts the program if allocation fails ****************/
extern char *xstrdup(const char *s);

/* Print the error message for failed call operation, using the errorno and
   and end the program */
extern void system_error(const char *operation);

/* Print an error message for failure involving CAUSE, including a
   descriptive MESSAGE, and end the program. */
extern void error(const char *cause, const char *message);

/* Return the directory containing the running program’s executable.
   The return value is a memory buffer that the caller must deallocate
   using free. This function calls abort on failure. */
extern char *get_self_executable_directory();

/* Symobls defined in module.c ***********************************************/

struct server_module {
    /* Shared lib corresponding to the module *******************************/
    void *handle;
    /* Name of the module ***************************************************/
    const char *name;
    /* the function that genrates the HTML results for this module **********/
    void *(*generate_function)(int);
};

/* dir where the modules are loaded ******************************************/
extern char *module_dir;

/* Attempt to load a server module with the name MODULE_PATH. If a
   server module exists with this path, loads the module and returns a
   server_module structure representing it. Otherwise, returns NULL. */
extern struct server_module *module_open(const char *module_path);

/* Close server module  and deallocate the Moudle object *********************/
extern void module_close(struct server_module *module);

/* Symbols defined in the server.c *******************************************/

extern void start_server(struct in_addr local_address, uint16_t port);

#endif
