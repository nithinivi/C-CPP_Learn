#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"

// HTTP 200 repsonse

static char *ok_response = "HTTP/1.0 200 OK\n"
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

static void clean_up_child_process(int signal_number) {
    int status;
    wait(&status);
}

static void handle_get(int connection_fd, const char *page) {
    struct server_module *module = NULL;

    if (*page == '/' && strchr(page + 1, '/') == NULL) {
        char module_file_name[64];
        // construct the module name by
        // appending ".so" to the page name
        snprintf(module_file_name, sizeof(module_file_name), "%s.so", page + 1);
        module = module_open(module_file_name);
    }
    if (module == NULL) {
        // return 404  Not Found
        char response[1024];
        snprintf(response, sizeof(response), not_found_response_template, page);

        // send it to the client
        write(connection_fd, response, strlen(response));
    } else {
        /* if the module was load successfully then the saned repinse
        page and the header */
        write(connection_fd, ok_response, strlen(ok_response));

        // invoke module , genrate the html and send to the client

        (*module->generate_function)(connection_fd);
        module_close(module);
    }
}

static void hanndle_connection(int connection_fd) {
    char buffer[255];
    // why would we need a signed size_t ?
    ssize_t bytes_read;

    bytes_read = read(connection_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        char method[sizeof(buffer)];
        char url[sizeof(buffer)];
        char protocal[sizeof(buffer)];
        // null terminating data to use string
        buffer[bytes_read] = '\0';

        sscanf(buffer, "%s %s %s", method, url, protocal);
        // read until the delimited black lines . In HTTP CR/LF
        while (strstr(buffer, "\r\n\r\n") == NULL)
            bytes_read = read(connection_fd, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            close(connection_fd);
            return;
        }

        // check the protocl field , We understand HTTP version 1.0 and 1.1.

        if (strcmp(protocal, "HTTP/1.0") && strcmp(protocal, "HTTP/1.1"))
            write(connection_fd, bad_method_response_template,
                  sizeof(bad_request_response));
        else if (strcmp(method, "GET")) {
            char response[1024];
            snprintf(response, sizeof(response), bad_method_response_template,
                     method);

            write(connection_fd, response, strlen(response));
        } else
            handle_get(connection_fd, url);
    }
}
