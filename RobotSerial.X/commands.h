/* 
 * File:   commands.h
 * Author: mauriliodc
 *
 * Created on 16 maggio 2013, 12.04
 */

#ifndef COMMANDS_H
#define	COMMANDS_H


//INTERNALS
//====================================================================

struct CommandsAndFunctions {
    unsigned char commandName[MAX_BUFF];
    void (*callback)(void);
};

struct CommandsAndFunctions commandsArray[COMMAND_SIZE];

int compareCommands(unsigned char* buffer, unsigned char* command) {
    unsigned char commandCode[2];
    memcpy((unsigned char*)commandCode,(unsigned char*)&buffer[1], 2*sizeof(char));

    if (strcmp((const char*) commandCode, (const char*) command) == 0)return 1;
    else return 0;
}

void assignCommand(const char* c, unsigned char* p) {
    strcpy((char*) p, c);
}
//COMMANDS
//====================================================================

void comando(void) {
    putsUART1((unsigned int *) "COMANDO 1");
}

void comando2(void) {
    putsUART1((unsigned int *) "COMANDO 2 volante");
}
//====================================================================

void generateCommands() {
    assignCommand("00", commandsArray[0].commandName);
    commandsArray[0].callback = &comando;

    assignCommand("06", commandsArray[1].commandName);
    commandsArray[1].callback = &comando2;
}

void parseAndExecuteCommand() {
    int i = 0;
    for (i = 0; i < COMMAND_SIZE; i++) {
        if (compareCommands(Buf, commandsArray[i].commandName)) {
            commandsArray[i].callback();
            return;
        };
    }
}



#endif	/* COMMANDS_H */

