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
char* writePacket(const struct Packet* p, char* buffer,int ascii);
//ParsePacket:
char* parsePacket(char* buffer, struct Packet* p,int ascii);
//
char* writeDummyPacket(const struct Packet* p, char* buffer, int ascii);
char* writeDumbPacket(const struct Packet* p, char* buffer, int ascii);

char* readDummyPacket(struct Packet* p,char* buffer, int ascii);
char* readDumbPacket(struct Packet* p,char* buffer, int ascii);
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
 char* writeChar(char value, char* buffer);
 char* writeUint8(uint8_t value, char* buffer);
 char* writeUint16(uint16_t value, char* buffer);
 char* writeUint32(uint32_t value, char* buffer);
 char* writeFloat(float value, char* buffer);
//------------------------------------------------------------------------------
//ASCII
//------------------------------------------------------------------------------
 char* writeCharAscii(char value, char* buffer);
 char* writeUint8Ascii(uint8_t value, char* buffer);
 char* writeUint16Ascii(uint16_t value, char* buffer);
 char* writeUint32Ascii(uint32_t value, char* buffer);
 char* writeFloatAscii(float value, char* buffer);

//READING
//------------------------------------------------------------------------------
//Binary
//------------------------------------------------------------------------------
 char*  readUint8(uint8_t* dest, char* buffer);
 char*  readUint16(uint16_t* dest, char* buffer);
 char*  readUint32(uint32_t* dest, char* buffer);
 char*  readFloat(float* dest, char* buffer);

 
//------------------------------------------------------------------------------
//ASCII
//------------------------------------------------------------------------------
 char* readUint8Ascii(char* dest, char* buffer );
 char* readUint16Ascii( char* dest, char* buffer);
 char* readUint32Ascii(char* dest, char* buffer);
 char* readFloatAscii(char* dest,char* buffer);



 //Checksum
 uint8_t computeChecksum(char* buffer, uint8_t length);