#ifndef MAL_PRIM
#define	MAL_PRIM
#include "Arduino.h"
#ifdef __cplusplus
extern "C" {
#endif



extern char packet_decoder_ascii_header;
extern char packet_decoder_ascii_footer;
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
char* writeHeaderAscii(char* buffer);
char* writeFooterAscii(char* buffer);
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
char* readFloatAscii(char* dest, char* buffer);
#ifdef __cplusplus
}
#endif
#endif

