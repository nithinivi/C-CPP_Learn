#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "payload.hpp"
#ifndef _SERVER_DOT_H
#define _SERVER_DOT_H

class CServerSocket {
    int m_ProtocolPort = 3500;
    struct sockaddr_in m_LocalAddress;

public:
    static struct sockaddr_in m_RemoteAddress;
    char m_Buffer[ 1024 ];
    static int m_ListnerSocket;
    pthread_t Thid;
    static void* ListenThreadProc(LPVOID lpParameter);
    static void* ClientThreadProc(LPVOID lpParam);

    CServerSocket(int p_port) {
        m_ProtocolPort = p_port;
        m_LocalAddress.sin_family = AF_INET;
        m_LocalAddress.sin_addr.s_addr = INADDR_ANY;
        m_LocalAddress.sin_port = htons(m_ProtocolPort);
    }

    bool Open() {

        if ((m_ListnerSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            return false;
        }
        printf("%s\n", "About to Bind.. ................ ");
        if (bind(m_ListnerSocket,
                 (struct sockaddr*)&m_LocalAddress, // casting to generic socket
                                                    // address
                 sizeof(m_LocalAddress)) == -1) {
            return false;
        }
        printf("%s\n", "Listen. ................ ");
        if (listen(m_ListnerSocket, 5) == -1) {
            return false;
        }
        StartListeningThread();
        return true;
    }

    bool StartListeningThread() {
        printf("%s\n", "Creating a  Posix Thread....... for Listener\n");
        pthread_create(&Thid, NULL, ListenThreadProc, NULL);
        return true;
    }
    ///////////////////////////////////////
    //
    //
    bool Close() {
        close(m_ListnerSocket);
        return false;
    }
};

#endif
