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
#define BUFFER_SIZE 255
#define MANY_COMMANDS 9

//PACKETS
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

extern uint8_t DumbPacketID;
struct DumbPacket{
    uint8_t stupid;
};

struct Packet{
    uint8_t id;
    uint8_t lenght;
    uint32_t seq;
    union{
        struct DummyPacket dummy;
        struct DumbPacket dumb;
    };
};

//==============================================================================

struct PacketDecoder{
    int ascii;
    int status;
    char buffer[BUFFER_SIZE];
    char* buffer_start;
    char* buffer_end;
    uint8_t lenght;
    uint8_t checksum;
};



enum BufferStatus {Unsync=0x0, Sync=0x1, Length=0x2, Payload=0x3};
extern char header_1;
extern char header_2;
//Utility functions to clear and prepare the encoder/decoder stuff.
//Call it before use it!
void DecoderInit(struct PacketDecoder* dm, int ascii);
void ResetDecoderBuffer(struct PacketDecoder* d);
int DecoderPutChar(struct PacketDecoder* d, char c);


//Packets Stuff

//WritePacket:
//gets a const packet to create a char array ready to be sent
void writePacket(const struct Packet* p, char* buffer,int ascii);
//ParsePacket:
void parsePacket(char* buffer, struct Packet* p,int ascii);
//
void writeDummyPacket(const struct Packet* p, char* buffer, int ascii);
void writeDumbPacket(const struct Packet* p, char* buffer, int ascii);

void readDummyPacket(struct Packet* p,char* buffer, int ascii);
void readDumbPacket(struct Packet* p,char* buffer, int ascii);
void initConsts();
////ParsePacket:
////gets a const char array and write parsed data on a Packet
//void parsePacket(const char* buffer, struct Packet* p);





//##############################################################################
//Conversion primitives
//##############################################################################
//READING
//------------------------------------------------------------------------------
//Binary
//------------------------------------------------------------------------------
//note: the writing binary primitives makes side effect on the buffer and returns
//the pointer to the new memory address to write on
char* WriteChar(char value, char* buffer);
char* WriteUint8(uint8_t value, char* buffer);
char* WriteUint16(uint16_t value, char* buffer);
char* WriteUint32(uint32_t value, char* buffer);
char* WriteFloat(float value, char* buffer);
//------------------------------------------------------------------------------
//ASCII
//------------------------------------------------------------------------------
int WriteCharAscii(char value, char* buffer);
int WriteUint8Ascii(uint8_t value, char* buffer);
int WriteUint16Ascii(uint16_t value, char* buffer);
int WriteUint32Ascii(uint32_t value, char* buffer);
int WriteFloatAscii(float value, char* buffer);

//READING
//------------------------------------------------------------------------------
//Binary
//------------------------------------------------------------------------------
uint8_t ReadUint8(char* buffer);
uint16_t ReadUint16(char* buffer);
uint32_t ReadUint32(char* buffer);
float ReadFloat(char* buffer);
//------------------------------------------------------------------------------
//ASCII
//------------------------------------------------------------------------------
void ReadUint8Ascii(char* buffer, char* dest);
void ReadUint16Ascii(char* buffer, char* dest);
void ReadUint32Ascii(char* buffer, char* dest);
void ReadFloatAscii(char* buffer, char* dest);