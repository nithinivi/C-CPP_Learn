// Server.cpp : Defines the entry point for the console application.
// under POSIX
// g++ -o Mserver.exe Mserver.cpp -lpthread
// ./Mserver.exe <port>
// under Windows
// cl /DWINDOWS_OS MServer.cpp ws2_32.lib
// Mserver <port>
//

#include <cstring>
#include <ctype.h>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "payload.hpp"
#include "server.hpp"

using namespace std;
////////////////////////////////

bool StartSocket(); //--- Initialize Socket Engine ..No code inside the Posix

typedef struct {
    int Sh; // Socket Handle which represents a Client
} CLIENT_DATA;
//---------------- Socket Descriptor for Windows
//---------------- Listener Socket => Accepts Connection
//---------------- Incoming Socket is Socket Per Client

int InComingSocket;
//----------------- Thread Entry Points for Listener and Thread Per Client
void* ListenThreadProc(LPVOID lpParameter);
void* ClientThreadProc(LPVOID lpParam);

//-----------------Get Last Socket Error
int SocketGetLastError() { return errno; }
//----------------- Close Socket
int CloseSocket(int s) {
    close(s);
    return 0;
}

struct sockaddr_in CServerSocket::m_RemoteAddress {};
int CServerSocket::m_ListnerSocket = -1;

void* CServerSocket::ListenThreadProc(LPVOID lpParameter) {

    printf("Entered the Listener Thread....\n");
    while (1) {
        unsigned int Len = sizeof(CServerSocket::m_RemoteAddress);
        InComingSocket =
            accept(CServerSocket::m_ListnerSocket,
                   (struct sockaddr*)&CServerSocket::m_RemoteAddress, &Len);
        printf("....................After the Accept........");
        if (InComingSocket == -1) {
            fprintf(stderr, "accept error %d\n", errno);
            // Cleanup();
            return 0;
        }
        printf("\n....................Accepted a new Connection........\n");
        CLIENT_DATA ClientData;
        pthread_t ThreadId;
        ClientData.Sh = InComingSocket;
        pthread_create(&ThreadId, NULL, CServerSocket::ClientThreadProc,
                       (LPVOID)&ClientData);
    }

    return 0;
}

bool ReadSocketBuffer(SOCKET s, char* bfr, int size) {
    int RetVal = recv(s, bfr, size, 0);
    if (RetVal == 0 || RetVal == -1)
        return false;
    return true;
}

bool SendAcknowledgement(SOCKET s) {

    T_ACK ack = MakeAck();
    int bytes_send = send(s, (char*)&ack, sizeof(ack), 0);
    return bytes_send > 0;
}

bool SendEOF(SOCKET s) {

    T_FILE_EOF eof = MakeEof();
    int bytes_send = send(s, (char*)&eof, sizeof(eof), 0);
    return bytes_send > 0;
}

void* CServerSocket::ClientThreadProc(LPVOID lpParam) {

    CLIENT_DATA CData;
    memcpy(&CData, lpParam, sizeof(CLIENT_DATA));
    char bfr[ 32000 ];

    memset(bfr, 0, 32000);
    int RetVal = recv(CData.Sh, bfr, sizeof(bfr), 0);
    if (RetVal == 0 || RetVal == -1)
        return 0;

    int packet_type = *((int*)bfr);
    printf("%d\n", packet_type);
    if (packet_type != 1) {
        cout << "could not receive the right packet" << endl;
        return 0;
    }
    T_ACK ack = MakeAck();
    int bytes_send = send(CData.Sh, (char*)&ack, sizeof(ack), 0);
    cout << "Finished Sending the Acknowledgement ... bytes send= "
         << bytes_send << endl;

    if (!ReadSocketBuffer(CData.Sh, bfr, sizeof(bfr))) {
        cout << "Failed to Read From Socket........"
             << "Exiting the App" << endl;
        return 0;
    }
    if (*((int*)bfr) != 3) {
        cout << "Expected Meta Data .... " << endl;
        return 0;
    }
    T_FILE_META file_meta_data;
    memcpy(&file_meta_data, bfr, sizeof(file_meta_data));
    cout << " file name = " << file_meta_data.file_name
         << " size = " << file_meta_data.size;
    SendAcknowledgement(CData.Sh);
    cout << "finished .....sending acknowledgement....."
         << "transferring files" << endl;
    cout << "Waiting for the content " << endl;
    FILE* fp = fopen("DEST_WIRE.out", "wb");
    char buffer_chunk[ 32000 ];
    int transferred_size = 0;
    while (1) {
        cout << "Transferred = " << transferred_size << endl;
        ReadSocketBuffer(CData.Sh, buffer_chunk, sizeof(buffer_chunk));
        cout << "Packet Type = " << *(int*)buffer_chunk << endl;

        if (*(int*)buffer_chunk == 5) {
            cout << "End of File Received" << endl;
            fclose(fp);
            SendAcknowledgement(CData.Sh);
            if (transferred_size != file_meta_data.size) {
                cout << "Expected Size = " << file_meta_data.size << endl;
                cout << "Received Size = " << transferred_size << endl;
            }
            return 0;
        }
        if (*(int*)buffer_chunk != 4) {
            cout << " I do not know what happens here" << endl;
            cout << "What kind of packet = " << *(int*)buffer_chunk << endl;
            fclose(fp);
            return 0;
        }

        T_FILE_CHUNK* chunk = (T_FILE_CHUNK*)buffer_chunk;
        char temp_mem[ 32000 ];
        cout << "Received Block ...... " << chunk->buffer_size << endl;
        memcpy(temp_mem, chunk->buffer, chunk->buffer_size);
        fwrite(temp_mem, 1, chunk->buffer_size, fp);
        transferred_size += chunk->buffer_size;
    }

    return 0;
}
int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stdout, "Usage: Server <portid> \n");
        return 1;
    }

    CServerSocket sock{atoi(argv[ 1 ])};
    sock.Open();

    while (1)
        ;
    // Cleanup();
    return 0;
}

/////////////////////////////////
//
// Initialise Winsock Libraries
//
//
//

/////////////////////////////////////
//
//
//
//
//
//
