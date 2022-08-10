#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "payload.hpp"

void Cleanup() {}

int SocketGetLastError() { return 0; }

class CClientSocket {
    char m_ServerName[ 255 ];
    int m_PortNumber;
    struct sockaddr_in m_Server;
    struct hostent* m_HostPointer;
    unsigned int m_addr;
    SOCKET m_ConnectSock;

public:
    CClientSocket(char* ServerName, int PortNumber) {
        strcpy(m_ServerName, ServerName);
        m_PortNumber = PortNumber;
    }
    SOCKET GetSocket() { return m_ConnectSock; }
    bool Resolve() {

        if (isalpha(m_ServerName[ 0 ])) {
            m_HostPointer = gethostbyname(m_ServerName);
        } else { /* Convert nnn.nnn address to a usable one */
            m_addr = inet_addr(m_ServerName);
            m_HostPointer = gethostbyaddr((char*)&m_addr, 4, AF_INET);
        }
        if (m_HostPointer == NULL) {
            return false;
        }

        memset(&m_Server, 0, sizeof(m_Server));

        memcpy(&(m_Server.sin_addr), m_HostPointer->h_addr,
               m_HostPointer->h_length);
        m_Server.sin_family = m_HostPointer->h_addrtype;
        m_Server.sin_port = htons(m_PortNumber);
        return true;
    }

    bool Connect() {
        m_ConnectSock = socket(AF_INET, SOCK_STREAM, 0);
        if (m_ConnectSock < 0) {
            return false;
        }

        if (connect(m_ConnectSock, (struct sockaddr*)&m_Server,
                    sizeof(m_Server)) < 0) {
            return false;
        }
        return true;
    }

    bool Send(void* buffer, int len) {
        int RetVal = send(m_ConnectSock, (const char*)buffer, len, 0);
        if (RetVal == -1) {
            return false;
        }

        return true;
    }

    bool Receive(void* buffer, int* len) {
        cout << "......................Received The Function.... " << endl;
        int RetVal = recv(m_ConnectSock, (char*)buffer, *len, 0);
        cout << "......................Received The Function.... " << RetVal
             << endl;

        if (RetVal == 0 || RetVal == -1) {
            printf("Error at socket(): %d\n", errno);
            return false;
        }

        *len = RetVal;
        return true;
    }

    int Close() {
        close(m_ConnectSock);
        return 0;
    }
};

bool SendEOF(SOCKET s) {

    T_FILE_EOF eof = MakeEof();
    int bytes_send = send(s, (char*)&eof, sizeof(eof), 0);
    return bytes_send > 0;
}

bool ReadSocketBuffer(SOCKET s, char* bfr, int size) {
    int RetVal = recv(s, bfr, size, 0);
    if (RetVal == 0 || RetVal == -1)
        return false;
    return true;
}

bool WriteSocketBuffer(SOCKET s, char* bfr, int size) {
    int RetVal = send(s, bfr, size, 0);
    if (RetVal == 0 || RetVal == -1)
        return false;
    return true;
}

bool SendAcknowledgement(SOCKET s) {

    T_ACK ack = MakeAck();
    int bytes_send = send(s, (char*)&ack, sizeof(ack), 0);
    return bytes_send > 0;
}

long ComputeFileSize(char* file_name) {
    ifstream in_file(file_name, ios::binary);
    in_file.seekg(0, ios::end);
    int file_size = in_file.tellg();
    return (long)file_size;
};

int main(int argc, char** argv) {

    if (argc != 4) {
        printf("insufficient command line arguments\n");
        return 0;
    }

    char* file_name = argv[ 1 ];
    char* server_name = argv[ 2 ];
    int port = atoi(argv[ 3 ]);
    int size_file = ComputeFileSize(file_name);
    printf("%s\t%dn", file_name, size_file);

    CClientSocket c_sock(server_name, port);
    if (!c_sock.Resolve()) {
        printf("Failed to Resolve Client Socket ............\n");
        return 1;
    }

    if (!c_sock.Connect()) {
        printf("Failed to Connect to the Server ............\n");
        return 1;
    }
    //------------------------- Protocol Part Comes here
    T_HAND_SHAKE send_packet = MakeHandShake();
    c_sock.Send(&send_packet, sizeof(send_packet));

    //------------- Waiting for Ack Packet
    char buffer[ 32 ];
    int num_read = 32;
    sleep(2000);
    if (!c_sock.Receive(buffer, &num_read)) {
        cout << "Could not Receive Packet " << endl;
        return 1;
    }
    T_ACK ack;
    memcpy(&ack, buffer, sizeof(T_ACK));
    if (ack.packet_type != 2) {

        cout << "Acknowledged Packet is not correct......" << endl;
        return 1;
    }
    cout << endl << "Ready to Transfer Files ...................\n" << endl;
    T_FILE_META file_meta_data = MakeFileMeta(file_name, size_file);
    c_sock.Send(&file_meta_data, sizeof(file_meta_data));
    if (!c_sock.Receive(buffer, &num_read)) {
        cout << "Could not Receive Packet " << endl;
        return 1;
    }

    memcpy(&ack, buffer, sizeof(T_ACK));
    if (ack.packet_type != 2) {

        cout << "Acknowledged Packet is not correct......" << endl;
        return 1;
    }
    cout << "Now, we will iterate to send the content of the file......"
         << endl;

    int num = 0;
    int chunk_size = sizeof(T_FILE_CHUNK) + 5000;
    int packet_sequence = 1;
    // T_FILE_CHUNK * chunk = (T_FILE_CHUNK *) malloc( chunk_size );
    FILE* fp = fopen(file_name, "rb");
    if (fp == nullptr) {

        cout << "Failed to Open File = " << file_name << endl;
        return 1;
    }
    cout << "Opened File.............." << file_name << endl;
    char read_buffer[ 4096 ];
    while ((num = fread(read_buffer, 1, 4096, fp)) == 4096) {
        cout << "Sequence ..... " << packet_sequence << endl;
        cout << "Sending Bytes..............." << num << endl;
        T_FILE_CHUNK* chunk =
            MakeBufferPack(read_buffer, 4096, packet_sequence++);
        cout << "Above sentence................" << endl;
        if (!c_sock.Send(chunk, chunk_size)) {
            cout << "Send Failure " << endl;
            break;
        }
        cout << "Sequence ..... " << packet_sequence << endl;

        free(chunk);
    }
    cout << "Residue = " << num << endl;
    cout << "Coming out of the Send Loop "
         << "Send Residue" << endl;
    if (num > 0) {
        T_FILE_CHUNK* chunk =
            MakeBufferPack(read_buffer, num, packet_sequence++);
        if (!c_sock.Send(chunk, chunk_size)) {
            cout << "Send Failure " << endl;
            return -1;
        }
    }
    fclose(fp);
    cout << "Finished Sending File "
         << " About to send EOF " << endl;
    SendEOF(c_sock.GetSocket());
    cout << "Finished Sending EOF " << endl;
    c_sock.Close();
    Cleanup();
}