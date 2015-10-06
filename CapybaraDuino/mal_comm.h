#ifndef MAL_COMM
#define	MAL_COMM
#include "Arduino.h"
#ifdef __cplusplus
extern "C" {
#endif


#include "mal_primitives.h"

#define BUFFER_SIZE 255

//==============================================================================
// SPEED PAYLOAD
//==============================================================================

extern uint8_t Speed_Payload_ID;

struct Speed_Payload {
  int16_t leftTick;
  int16_t rightTick;
};
//==============================================================================


//==============================================================================
//PACKET
//==============================================================================

struct Packet {
  uint8_t id;
  uint8_t lenght;
  uint32_t seq;

  union {
    struct Speed_Payload speed;
  };
};
//==============================================================================


//==============================================================================
//DECODER
//==============================================================================
struct Packet_Decoder {
  int ascii;
  int status;
  char buffer[BUFFER_SIZE];
  char* buffer_start;
  char* bufferPtr;
  uint8_t lenght;
  uint8_t checksum;
};
//==============================================================================

//Externs and Union
//==============================================================================

enum buffer_status {
  Unsync = 0x0, Sync = 0x1, Length = 0x2, Payload = 0x3
};
extern char packet_decoder_binary_header_1;
extern char packet_decoder_binary_header_2;
extern char packet_decoder_ascii_header;
extern char packet_decoder_ascii_footer;


//Packets Stuff
//==============================================================================
//WritePacket:
//gets a const packet to create a char array ready to be sent
char* Packet_write(const struct Packet* p, char* buffer, int ascii);
//ParsePacket:
char* Packet_parse(char* buffer, struct Packet* p, int ascii);
//Execute
int Packet_execute(struct Packet* p);
//==============================================================================
//[WR]SPEED PACKET
char* Speed_Payload_write(const struct Packet* p, char* buffer, int ascii);
char* Speed_Payload_read(struct Packet* p, char* buffer, int ascii);
void Speed_Payload_execute(struct Packet* p);
//==============================================================================

//DECODER STUFF
//Utility functions to clear and prepare the encoder/decoder stuff.
//Call it before use it!
//==============================================================================
void Packet_Decoder_init(struct Packet_Decoder* dm, int ascii);
void Packet_Decoder_resetBuffers(struct Packet_Decoder* d);
int Packet_Decoder_putChar(struct Packet_Decoder* d, char c);
void Dummy_Payload_execute(struct Packet* p);
//==============================================================================
//==============================================================================

//GenericStuff
//==============================================================================
void initConsts();
//Checksum
uint8_t Payload_computeChecksum(char* buffer, uint8_t length);
//==============================================================================
//==============================================================================
#ifdef __cplusplus
}
#endif
#endif

