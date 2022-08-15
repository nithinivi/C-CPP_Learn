#include <fstream>
#include <iostream>

#ifndef _PAYLOAD_DOT_H
#define _PAYLOAD_DOT_H

typedef unsigned long DWORD;
typedef void *LPVOID;
typedef int SOCKET;

//----------------------- Packet Types for the Wire Level Protocol for the FILE
// transfer
enum PacketType {
    CHISTA_NULL = -1,
    CHISTA_HAND_SHAKE = 1,      // sends "hello"
    CHISTA_ACK = 2,             // "olleh"
    CHISTA_META_DATA = 3,       // sends file_name and size
    CHISTA_FILE_CONTENT = 4,    // sends chunks of 4096
    CHISTA_META_EOF = 5,        // sends the End of File Token
    CHISTA_META_FATAL_ERROR = 6 // sends the Fatal Error message
};

typedef struct {
    int packet_type;
    char hello_str[6];
    char padding[2];
} T_HAND_SHAKE;

typedef struct {
    int packet_type;
    char hello_str[6];
    char padding[2];
} T_ACK;

typedef struct {
    int packet_type;
    char file_name[255];
    long size;
    char padding[1];
} T_FILE_META;

typedef struct {
    int packet_type;
    int packet_seq_num;
    int buffer_size;
    char buffer[1];
} T_FILE_CHUNK;

typedef struct {
    int packet_type;
    char eof_str[4];
} T_FILE_EOF;

typedef struct {
    int packet_type;
    char err_msg[1020];
} T_FILE_FATAL_ERROR;

// Function for generating Packets
T_FILE_META MakeFileMeta(char *file_name, long size);
T_HAND_SHAKE MakeHandShake();
T_ACK MakeAck();
T_FILE_EOF MakeEof();
T_FILE_CHUNK *MakeBufferPack(void *buffer, int len, int);
T_FILE_FATAL_ERROR MakeErrorPack(char *buffer, int len);
//------------ Compute The file Size
// long ComputeFileSize(char* file_name) ;

#endif
