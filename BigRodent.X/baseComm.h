/* 
 * File:   baseComm.h
 * Author: malcom
 *
 * Created on July 26, 2013, 11:51 AM
 */

#ifndef BASECOMM_H
#define	BASECOMM_H

#define MAX_COMMANDS 16

struct command{
    int header;
    char* payload;
    void (*callback)(void);
    void (*response)(void);
    void (*parser)(void);
};



int commandInit(struct command*);
void commandListCleaner();

#endif	/* BASECOMM_H */

