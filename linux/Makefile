CCOPTS=-g -Wall
CPPOPTS=-D_LINUX_
LIBS = -lserial 

CC = g++ -L  -g

OBJS = 	hexmessage.o \
	packet_handler.o \
	platform_defs.o \
	querycommands_packet.o \
	speed_packet.o \
	state_packet.o \
	pid_packet.o \
	odometrycalib_packet.o \
	packets.o \
 #	timer_handler.o 
 
#all: 	timer_test packet_test packet_read_execute packet_generate
all: 	packet_test packet_read_execute packet_generate

#timer_test: $(OBJS) timer_test.c
#	$(CC) $(CCOPTS) $(CPPOPTS) -o $@  $^    

packet_generate: $(OBJS) packet_generate.c
	$(CC) $(CCOPTS) $(CPPOPTS) -o $@  $^ $(LIBS)

packet_read_execute: $(OBJS) packet_read_execute.c
	$(CC) $(CCOPTS) $(CPPOPTS)  -o $@  $^ $(LIBS)

packet_test: $(OBJS) packet_test.c
	$(CC) $(CCOPTS) $(CPPOPTS) $(LDLIBS)-o $@  $^    


%.o:	%.c %.h
	$(CC) $(CCOPTS) $(CPPOPTS) $(LDLIBS) -c -o $@   $<  


clean:
	rm -rf *.o *~ timer_test packet_test packet_read_execute packet_generate
