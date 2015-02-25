OBJS =	MalComm.o\
main.o \
primitives.o \
DumbPacket.o \
DummyPacket.o \
InitPacket.o \
SlimStatePacket.o \
SpeedPacket.o


all: mal

clean:
	rm -rf *.o *~$ *.gch mal

mal: $(OBJS)
	$(CC) -o malCommTester -g $(OBJS)

%.o:	%.c
	$(CC) -c -g  $^
