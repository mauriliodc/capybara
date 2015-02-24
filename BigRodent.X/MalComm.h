/* 
 * File:   MalComm.h
 * Author: malcom
 *
 * Created on February 17, 2015, 11:27 PM
 */

#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <p33FJ128MC802.h>
#include "primitives.h"
#include "generic_utils.h"
#define BUFFER_SIZE 255


//PACKETS
//==============================================================================
//==============================================================================

//DUMB PACKET
//==============================================================================
extern uint8_t DumbPacketID;
struct DumbPacket{
    uint8_t stupid;
};
//==============================================================================


//DUMMY PACKET
//==============================================================================
extern uint8_t DummyPacketID;
struct DummyPacket{
    uint8_t field_1;
    uint16_t field_2;
    int8_t field_3;
    char field_4;
    float field_5;
    unsigned char field_6;
    uint32_t field_7;
    int32_t field_8;
};
//==============================================================================

struct Packet{
    uint8_t id;
    uint8_t lenght;
    uint32_t seq;
    union{
        struct DummyPacket dummy;
        struct DumbPacket dumb;
    };
};

struct PacketDecoder{
    int ascii;
    int status;
    char buffer[BUFFER_SIZE];
    char* buffer_start;
    char* bufferPtr;
    uint8_t lenght;
    uint8_t checksum;
};
//==============================================================================
//==============================================================================



//Externs and Union
//==============================================================================
enum BufferStatus {Unsync=0x0, Sync=0x1, Length=0x2, Payload=0x3};
extern char header_1;
extern char header_2;
extern char AsciiHeader;
extern char AsciiFooter;
//==============================================================================
//==============================================================================


//Packets Stuff
//==============================================================================
//WritePacket:
//gets a const packet to create a char array ready to be sent
char* writePacket(const struct Packet* p, char* buffer,int ascii);
//ParsePacket:
char* parsePacket(char* buffer, struct Packet* p,int ascii);
//==============================================================================


//[WR]DUMMY PACKET
char* writeDummyPacket(const struct Packet* p, char* buffer, int ascii);
char* readDummyPacket(struct Packet* p,char* buffer, int ascii);
//==============================================================================
//[WR]DUMB PACKET
char* writeDumbPacket(const struct Packet* p, char* buffer, int ascii);
char* readDumbPacket(struct Packet* p,char* buffer, int ascii);
//==============================================================================



//DECODER STUFF
//Utility functions to clear and prepare the encoder/decoder stuff.
//Call it before use it!
//==============================================================================
void DecoderInit(struct PacketDecoder* dm, int ascii);
void ResetDecoderBuffer(struct PacketDecoder* d);
int DecoderPutChar(struct PacketDecoder* d, char c);
//==============================================================================
//==============================================================================




//GenericStuff
//==============================================================================
void initConsts();
//Checksum
uint8_t computeChecksum(char* buffer, uint8_t length);
//==============================================================================
//==============================================================================


#ifdef __33FJ128MC802_H
//Generic send to uart
void sendToUart(char* buffer,int length, int intraCharDelayUs);
#else
void sendToUart(int device, char* buffer, int length, int intraCharDelayUs);
#endif