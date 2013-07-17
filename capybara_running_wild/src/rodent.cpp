#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include "serialFriend.h"
#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"
#include <unistd.h>
#include <pthread.h>
#define MAX_BUFFER_SIZE 1024
char outputBuffer[MAX_BUFFER_SIZE]; // where we write our responses
char joyBuffer[MAX_BUFFER_SIZE]; // where we write our responses
HexMessage outputStream; // wrappers to the char arrays with counters
HexMessage joyStream; // wrappers to the char arrays with counters
char packetBuffer [MAX_BUFFER_SIZE]; // where we write our deserialized packet
HexMessage inputStream;
PacketHeader * parsedPacket = (PacketHeader *) packetBuffer;
char c[500];
int i=0;
SerialFriend* s;
char _HEADER='$';
char _FOOTER='%';

struct Robbo {
  Robbo() {
    _serialFriend = 0;
    _lastCommand = 0;
    StatePacket_initHeader(&_statePacket);
    SpeedPacket_initHeader(&_speedPacket);
    WheelSpeedPacket_initHeader(&_wheelSpeedPacket);

    parsedPacket = (PacketHeader *) packetBuffer;
    HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
    HexMessage_setBuffer(&inputStream, inputBuffer, MAX_BUFFER_SIZE);
  }

  bool openConnection(std::string device){
    _serialFriend = new SerialFriend(device, B115200);
    return true;
  }

  void closeConnection(){
    if (_serialFriend) {
      delete _serialFriend;
      _serialFriend = 0;
    }
  }

  bool isConnectionOpen() const {
    return _serialFriend;
  }

  void handleComm()
  {
  	//printf("handlecomm\n");
	char* bstart=c;
	char* bcurr=c;
	char* bend=(c+500);
	int receiving_command=0;
	char cc;
	if(this->_serialFriend->read(&cc)>0)
		printf("%c",cc);
/*
while(this->_serialFriend->read(&cc)){
    	//printf("not receiving_command\n");
    if(cc!=' ' || cc!='\0'){
	    printf("%c",cc);
	    if(cc=='$' && !receiving_command)
	    {
	    	//printf("receiving_command\n");
		receiving_command=1;
		*bcurr =cc;
		bcurr++;
	    }
	    else if (bcurr<bend-1 && receiving_command){
		*bcurr =cc;
		bcurr++;
		if (cc=='%'){
		    //printf("commmand ok \n");
		    int size = bcurr-bstart;
		    if(inputStream.end-inputStream.current>size) {
		        memcpy(inputStream.current,bstart+1,size-2);
		        inputStream.current += size-2;
		        *inputStream.current = '\0';
		        receiving_command=0;
		    }
		    bcurr = bstart;
		}
	    }
	    }
	}
	*/
  }

void setWheelSpeed(int lws, int rws){
  WheelSpeedPacket_initHeader(&_wheelSpeedPacket);
  _wheelSpeedPacket.leftSpeed = lws;
  _wheelSpeedPacket.rightSpeed = rws;
  _lastCommand = (PacketHeader*)(&_wheelSpeedPacket);
} 
  
StatePacket _statePacket;
SpeedPacket _speedPacket;
WheelSpeedPacket _wheelSpeedPacket;
SerialFriend* _serialFriend;
char outputBuffer[MAX_BUFFER_SIZE];
char inputBuffer[MAX_BUFFER_SIZE];
HexMessage inputStream;
HexMessage outputStream;
  
PacketHeader* _lastCommand;
char packetBuffer [MAX_BUFFER_SIZE]; // where we write our deserialized packet
PacketHeader * parsedPacket;

};

void PacketHandlerLoop(HexMessage* inputStream, HexMessage* outputStream){
  int error=0;
  HexMessage_reset(outputStream);
  while(! error && 
	inputStream->current!=inputStream->end){
    enum HexMessageStatus status=Packet_read(inputStream,parsedPacket);
    if (status==Ok ) {
      if (parsedPacket->type>=0){
      	//Packet_print(parsedPacket);
	Packet_execute(parsedPacket, outputStream);
      }
      

    } else  {
      printf("Parsing error %d \n",status);
      error = 1;
    }
  }
}


Robbo* robbo=0;

void joystickCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  //ROS_INFO("Translation: [%f] Rotation [%f]", msg->linear.x, msg->angular.z);

  float numba = 50.0f;
  robbo->setWheelSpeed(numba*msg->linear.x, numba*msg->linear.x);

  // w.leftSpeed=20;
  // w.rightSpeed=20;
  // Packet_write(&outputStream,(const struct PacketHeader*)&w);
  // s->write(outputStream.start);
  // std::cerr<<outputStream.start<<std::endl;
  // HexMessage_reset(&outputStream);

}


void *ReadFromUart(void* a)
{

  while(1)
  {
    robbo->handleComm();
  }
  return NULL;
}



int main(int argc, char **argv)
{
  PacketHandler_init();
  robbo = new Robbo();
  robbo->openConnection(argv[1]);

  Packets_init();

  //HexMessage_setBuffer(&outputStream, outputBuffer, MAX_BUFFER_SIZE);
  printf("opening %s \n",argv[1]);
  //s= new SerialFriend(argv[1],B115200);
  pthread_t threads[5];
  pthread_create(&threads[0], NULL, ReadFromUart,NULL);
  
  
  printf("Startin up...\n");
  ros::init(argc, argv, "capybara");
  printf("Init...\n");
  ros::NodeHandle n;
  printf("Node handle...\n");
  ros::Subscriber sub = n.subscribe("/cmd_vel", 1000, joystickCallback);
  printf("Subscribed!\n");



  
  
  ros::spin();
   
  return 0;
}
 
