#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>

//------------ All the prototypes for Payloads are given in the payload.h
#include "payload.hpp"
using namespace std;

///////////////////////
// Generates a PDU (Protocol Data Unit) for transferring file information
//
T_FILE_META MakeFileMeta(char* file_name, long size) {
    T_FILE_META ret_val;
    memset(&ret_val, 0, sizeof(T_FILE_META));
    ret_val.packet_type = CHISTA_META_DATA;
    strcpy(ret_val.file_name, file_name);
    ret_val.size = size;
    return ret_val;
}

//------ Generating HandShake PDU .... just sends hello
T_HAND_SHAKE MakeHandShake() {
    T_HAND_SHAKE ret_val;
    memset(&ret_val, 0, sizeof(T_HAND_SHAKE));
    ret_val.packet_type = CHISTA_HAND_SHAKE;
    strcpy(ret_val.hello_str, "hello");
    return ret_val;
}

//-------------------Generating ACK PDU ... olleh
T_ACK MakeAck() {
    T_ACK ret_val;
    memset(&ret_val, 0, sizeof(T_ACK));
    ret_val.packet_type = CHISTA_ACK;
    strcpy(ret_val.hello_str, "olleh");
    return ret_val;
}

//-------------- Sends the End of File Transfer
T_FILE_EOF MakeEof() {
    T_FILE_EOF ret_val;
    memset(&ret_val, 0, sizeof(T_FILE_EOF));
    ret_val.packet_type = CHISTA_META_EOF;
    strcpy(ret_val.eof_str, "EOF");
    return ret_val;
}

T_FILE_CHUNK* MakeBufferPack(void* buffer, int len, int seq_num) {
    int actual_buffer_size = sizeof(T_FILE_CHUNK) + len + 4;
    T_FILE_CHUNK* ret_val = (T_FILE_CHUNK*)malloc(actual_buffer_size);
    memset(ret_val, 0, actual_buffer_size);
    ret_val->packet_type = CHISTA_FILE_CONTENT;
    ret_val->packet_seq_num = seq_num;
    ret_val->buffer_size = len;
    memcpy(ret_val->buffer, buffer, len);
    return ret_val;
}

T_FILE_FATAL_ERROR MakeErrorPack(char* buffer, int len) {
    T_FILE_FATAL_ERROR ret_val;
    memset(&ret_val, 0, sizeof(T_FILE_FATAL_ERROR));
    ret_val.packet_type = CHISTA_META_FATAL_ERROR;
    if (len < 1020)
        strcpy(ret_val.err_msg, buffer);
    else {
        strcpy(ret_val.err_msg, "Error Message Too Long...");
    }
    return ret_val;
}
