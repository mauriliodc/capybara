CCOPTS=-g -Wall

CPPOPTS=-D_LINUX_

CC = gcc

OBJS = 	hexmessage.o \
	packet_handler.o \
	platform_defs.o \
	querycommands_packet.o \
	speed_packet.o \
	state_packet.o \
	pid_packet.o \
	odometrycalib_packet.o \
	packets.o \
	timer_handler.o 
 
all: 	timer_test packet_test packet_read_execute packet_generate

timer_test: $(OBJS) timer_test.c
	$(CC) $(CCOPTS) $(CPPOPTS) -o $@  $^    

packet_generate: $(OBJS) packet_generate.c
	$(CC) $(CCOPTS) $(CPPOPTS) -o $@  $^    

packet_read_execute: $(OBJS) packet_read_execute.c
	$(CC) $(CCOPTS) $(CPPOPTS) -o $@  $^    

packet_test: $(OBJS) packet_test.c
	$(CC) $(CCOPTS) $(CPPOPTS) -o $@  $^    


%.o:	%.c %.h
	$(CC) $(CCOPTS) $(CPPOPTS) -c -o $@   $<  


clean:
	rm -rf *.o *~ timer_test packet_test packet_read_execute packet_generate