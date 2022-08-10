#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

char *module_dir;

struct server_module *module_open(const char *module_name) {
    char *module_path;
    void *handle;
    void (*module_generate)(int);
    struct server_module *module;

    // Construct the fullpath of the shared library
    module_path = (char *)xmalloc(strlen(module_dir) + strlen(module_name) + 2);
    sprintf(module_path, "%s/%s", module_dir, module_name);

    // attempt to open the module_path as shared lib
    handle = dlopen(module_path, RTLD_NOW);
    if (handle == NULL)
        // fails if the path doesn;t exist or it isnt a shared library.
        return NULL;

    // resolve the module_genrate symbol from standard library
    module_generate = (void (*)(int))dlsym(handle, "module_generate");
    if (module_generate == NULL) {
        dlclose(handle);
        return NULL;
    }
    /* symbol is */

    // Allocate & initialize a server module object

    module = (struct server_module *)xmalloc(sizeof(struct server_module));
    module->handle = handle;
    module->name = xstrdup(module_name);
    module->generate_function = module_generate;
    return module;
}

void module_close(struct server_module *module) {
    // close the share lib
    dlclose(module->handle);
    // de allocate the module name
    free((char *)module->name);
    // de allocate the moduel object
    free(module);
}
