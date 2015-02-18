/* 
 * File:   MalComm.h
 * Author: malcom
 *
 * Created on February 17, 2015, 11:27 PM
 */

#pragma once

#include <stdint.h>
#include <string.h>

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
    int lenght;
};

struct PacketEncoder{
    int ascii;
    int status;
    char buffer[BUFFER_SIZE];
    char* buffer_start;
    char* buffer_end;
    int lenght;
};


enum BufferStatus {Unsync=0x0, Sync=0x1, Length=0x2, Payload=0x3};
extern char header_1;
extern char header_2;
//Utility functions to clear and prepare the encoder/decoder stuff.
//Call it before use it!
void DecoderInit(struct PacketDecoder* d);
void EncoderInit(struct PacketEncoder* e);
void ResetDecoderBuffer(struct PacketDecoder* d);
void ResetEncoderBuffer(struct PacketEncoder* e);


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


//Conversion primitives
char* WriteChar(char value, char* buffer);
char* WriteUint8(uint8_t value, char* buffer);
char* WriteUint16(uint16_t value, char* buffer);
char* WriteUint32(uint32_t value, char* buffer);
char* WriteFloat(float value, char* buffer);

uint8_t ReadUint8(char* buffer);
uint16_t ReadUint16(char* buffer);
uint32_t ReadUint32(char* buffer);
float ReadFloat(char* buffer);

