#include "capybara.h"

Capybara::Capybara()
{
    this->_serialFriend=0;
    this->_lastCommand=0;
    StatePacket_initHeader(&this->_statePacket);
    SpeedPacket_initHeader(&this->_speedPacket);
    WheelSpeedPacket_initHeader(&this->_wheelSpeedPacket);
    parsedPacket = (PacketHeader *) packetBuffer;
    HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
    HexMessage_setBuffer(&inputStream, inputBuffer, MAX_BUFFER_SIZE);

    this->bstart=this->c;
    this->bcurr=this->c;
    this->bend=(c+MAX_BUFFER_SIZE);
    this->receiving_command=0;
}

Capybara::~Capybara()
{

}


bool Capybara::openConnection(std::string device)
{
    _serialFriend = new SerialFriend(device, B115200);
    return true;
}

void Capybara::closeConnection()
{
    if (this->_serialFriend) {
        delete this->_serialFriend;
        this->_serialFriend = 0;
    }
}

bool Capybara::isConnectionOpen() {
    return this->_serialFriend;
}


void Capybara::handleCommunication()
{
    char cc;
    while(1)
    {
        if(this->_serialFriend->read(&cc)<0)
        {
            continue;
        }

        if(cc==this->_serialFriend->getHeader())
        {
            receiving_command=1;
            *bcurr =cc;
            bcurr++;
        }
        else if (bcurr<bend-1 && receiving_command)
        {
            if (cc==this->_serialFriend->getFooter()){
                int size = bcurr-bstart;

                HexMessage_setBuffer(&inputStream, &c[1], size-2); // skip the newline
                //printf("SIZE [%d] incoming packet: [%s]\n",size,inputStream.start);
                //HexMessage_rewind(&inputStream);

                //MOMENTANEO
                PacketHandlerLoop(&inputStream,&outputStream);
                HexMessage_reset(&inputStream);
                memset(c,'\0',size);
                printf("%s \n",c);
                receiving_command=0;
                bcurr = bstart;
            }
            if(cc!=this->_serialFriend->getFooter())
            {
                *bcurr =cc;
                bcurr++;
            }
        }

        if (_lastCommand)
        {
            Packet_write(&outputStream,_lastCommand);
            this->_serialFriend->write(outputStream.start);
            HexMessage_reset(&outputStream);
            _lastCommand=0;
        }
        usleep(500);
    }
}

void Capybara::setWheelSpeed(int lws, int rws)
{
    WheelSpeedPacket_initHeader(&this->_wheelSpeedPacket);
    this->_wheelSpeedPacket.leftSpeed = lws;
    this->_wheelSpeedPacket.rightSpeed = rws;
    this->_lastCommand = (PacketHeader*)(&this->_wheelSpeedPacket);
}


void Capybara::PacketHandlerLoop(HexMessage* inputStream, HexMessage* outputStream){
    int error=0;
    HexMessage_reset(&this->outputStream);
    while(! error && this->inputStream.current!=this->inputStream.end){
        enum HexMessageStatus status=Packet_read(&this->inputStream,this->parsedPacket);
        if (status==Ok )
        {
            printf("STATUS %d\n",status);
            if (this->parsedPacket->type>=0)
            {
                printf("PRINT\n");
                Packet_print(this->parsedPacket);
                printf("EXECUTE\n");
                //Packet_execute(parsedPacket, outputStream);
            }
        }
        if (status!=Ok )
        {
            printf("Parsing error %d \n",status);
            error = 1;
        }
    }
}
