#ifndef _CAPYBARA_H
#define _CAPYBARA_H

#include "serialFriend.h"
#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

class Capybara{

public:
    Capybara();
    ~Capybara();
    bool openConnection(std::string device);
    void closeConnection();
    bool isConnectionOpen();
    void handleCommunication();
    void setWheelSpeed(int lws, int rws);
    void PacketHandlerLoop(HexMessage* inputStream, HexMessage* outputStream);
private:
    SerialFriend* _serialFriend;
    PacketHeader* _lastCommand;
    char outputBuffer[MAX_BUFFER_SIZE];
    char inputBuffer[MAX_BUFFER_SIZE];
    HexMessage outputStream;
    HexMessage inputStream;
    PacketHeader* parsedPacket;
    StatePacket _statePacket;
    SpeedPacket _speedPacket;
    WheelSpeedPacket _wheelSpeedPacket;
    char packetBuffer [MAX_BUFFER_SIZE];

    char* bstart;
    char* bcurr;
    char* bend;
    char c[MAX_BUFFER_SIZE];
    int receiving_command;

};





#endif
