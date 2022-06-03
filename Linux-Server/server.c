#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"


// HTTP 200 repsonse

static char* ok_response =
     "HTTP/1.0 200 OK\n"
     "Content-type : text/html\n"
     "\n";

/* HTTP response, header, and body, indicating that we didn’t
understand the request. */
static char *bad_request_response =
     "HTTP/1.0 400 Bad Request\n"
     "Content-type : text/html\n"
     "\n"
     "<html>\n"
     " <body>\n"
     " <h1> Bad Request</h1>\n"
     " <p> This server did not understand your request.</p>\n"
     " </body>\n"
     "</html>\n";

/* HTTP response, header, and body template, indicating that the
requested document was not found. */
static char *not_found_response_template =
     "HTTP/1.0 404 Not Found\n"
     "Content-type : text/html\n"
     "\n"
     "<html>\n"
     " <body>\n"
     " <h1> Not Found</h1>\n"
     " <p> The requested URL % s was not found on this server.</p>\n"
     " </body>\n"
     "</html>\n";

/* HTTP response, header, and body template, indicating that the
method was not understood. */
static char *bad_method_response_template =
     "HTTP / 1.0 501 Method Not Implemented\n"
     "Content - type : text / html\n"
     "\n"
     "<html>\n"
     " <body>\n"
     " <h1> Method Not Implemented</h1>\n"
     " <p> The method % s is not implemented by this server.</p>\n"
     " </body>\n"
     "</html>\n";

static void clean_up_child_process(int signal_number)
{
     int status;
     wait(&status);
}

static void handle_get(int connection_fd, const char *page)
{
     struct server_module* module = NULL;
     if (*page == '/' && strchr(page+1, '/') == NULL)
     {
          char module_file_name[64];
          snprintf(module_file_name,sizeof(module_file_name),"%s.so", page+1);
          module = module_open(module_file_name);
     }

     // if fails to load the module
     if (module == NULL)
     {
          char response[1024];
          snprintf(response, sizeof(response), not_found_response_template, page);
          write(connection_fd, response, strlen(response));
     }

     else {
       write(connection_fd, ok_response, strlen(ok_response));
       (*module->generate_function)(connection_fd);
       module_close(module);
     }
}
