#include "hexmessage.h"

static char ctable [] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

inline unsigned char asciiDigitToHex(unsigned char c){
  if (c<'A')
    return c-'0';
  return c-'A'+10;
}

int HexMessage_nextIsString(const HexMessage *msg){
  return (msg->current<msg->end && *msg->current=='\"');
}

enum HexMessageStatus HexMessage_writeHex(HexMessage* msg, const void* buf, int size){
  const unsigned char* b=(const unsigned char*)buf;
  int i;
  for (i=0; i<size; i++, b++){
    if (msg->end-msg->current<2)
      return WriteOverflow;
    unsigned char c=*b;
    *msg->current=ctable[c>>4];
    msg->current++;
    *msg->current=ctable[c&0x0F];
    msg->current++;
  }
  return Ok;
}

enum HexMessageStatus HexMessage_writeString(HexMessage *msg, const char* s){
  if (msg->end==msg->current)
    return WriteOverflow;
  *msg->current='\"';
  msg->current++;
  while(*s){
    if (msg->end==msg->current)
      return WriteOverflow;
    *msg->current=*s;
    msg->current++;
    s++;
  }
  if (msg->end==msg->current)
      return WriteOverflow;
  *msg->current='\"';
  msg->current++;
  return Ok;
}

enum HexMessageStatus HexMessage_readHex(HexMessage *msg, void* buf, int size){
  unsigned char* dest=(unsigned char*)buf;
  int i;
  for (i=0; i<size; i++, dest++){
    if (msg->end-msg->current<2)
      return WriteOverflow;
     unsigned char s=*msg->current; 
     msg->current++;
     unsigned char d=asciiDigitToHex(s)<<4;
     s=*msg->current; 
     d|=asciiDigitToHex(s);
     msg->current++;
     *dest=d;
  }
  return Ok;
}

enum HexMessageStatus HexMessage_readString(HexMessage *msg, unsigned char* s){
  if (msg->end==msg->current)
    return ReadUnderflow;
  if(*msg->current!='\"')
    return FormatError;
  msg->current++;
  while(msg->current!=msg->end){
    if (*msg->current=='\"') {
      *s=0;
      msg->current++;
      return Ok;
    }
    *s=*msg->current;
    s++;
    msg->current++;
  }
  return ReadUnderflow;
}



// sets the buffer to an external memory area
void HexMessage_setBuffer(HexMessage* msg, char* buffer, int bufferSize){
  msg->start = msg->current = buffer;
  msg->end = msg->bufferEnd = buffer+bufferSize;
}

// rewinds the buffer, the new end is the last character written
void HexMessage_rewind(HexMessage* msg){
  msg->end     = msg->current;
  msg->current = msg->start;
}

// resets the buffer the end is set to bufferEnd
void HexMessage_reset(HexMessage* msg){
  msg->current=msg->start;
  msg->end=msg->bufferEnd;
}

