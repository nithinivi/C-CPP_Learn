#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>


#include "server.h"


char* module_dir;


struct server_module* module_open(const char* module_name)
{
     char* module_path;
     void* handle;
     void (* module_generate) (int);
     struct server_module* module;

     // Construct the fullpath of the shared library
     module_path = (char*) xmalloc(strlen(module_dir) + strlen(module_name) + 2);
     sprintf(module_path, "%s/%s", module_dir, module_name);

     //attempt to open the module_path as shared lib
     handle = dlopen(module_path, RTLD_NOW);
     if (handle == NULL)
          return NULL;

     // resolve the module_genrate symbol from standard library
     module_generate = (void (*)(int)) dlsym(handle, "module_generate");
     if (module_generate == NULL) {
          dlclose(handle);
          return NULL;
     }


     // Allocate & initialize a server module object

     module = (struct server_module*) xmalloc(sizeof(struct server_module));
     module->handle = handle;
     module->name = xstrdup(module_name);
     module->generate_function = module_generate;
     return module;

}

void module_close(struct server_module *module)
{
     dlclose(module->handle);
     free ((char*) module->name);
     free (module);
}
