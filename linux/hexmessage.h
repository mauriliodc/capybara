#ifndef _HEX_MESSAGE_H_
#define _HEX_MESSAGE_H_

#include "platform_defs.h"

typedef struct HexMessage{
  char* start;
  char* current;
  char* end;
  char* bufferEnd;
} HexMessage;

enum HexMessageStatus {
  Ok=0x0, 
  WriteOverflow=0x1, 
  ReadUnderflow=0x2,
  FormatError=0x3,
  UnknownMessage=0x4
};

// sets the buffer to an external memory area
void HexMessage_setBuffer(HexMessage* msg, char* buffer, int bufferSize);

// rewinds the buffer, the new end is the last character written
void HexMessage_rewind(HexMessage* msg);

// resets the buffer the end is set to bufferEnd
void HexMessage_reset(HexMessage* msg);



enum HexMessageStatus HexMessage_writeHex(HexMessage* msg, const void* buf, int size);

enum HexMessageStatus HexMessage_writeString(HexMessage *msg, const char* s);

int HexMessage_nextIsString(const HexMessage *msg);

enum HexMessageStatus HexMessage_readHex(HexMessage *msg, void* buf, int size);

enum HexMessageStatus HexMessage_readString(HexMessage *msg, unsigned char* s);

#endif
