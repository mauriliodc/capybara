/* 
 * File:   WheelVelocityCommand.h
 * Author: malcom
 *
 * Created on July 26, 2013, 11:45 AM
 */

#ifndef WHEELVELOCITYCOMMAND_H
#define	WHEELVELOCITYCOMMAND_H

#include "baseComm.h"

void WheelVelocityCommandInit();
void WheelVelocityCallback();
void WheelVelocityResponse();

extern struct wheelVelocityCommand WheelVelocityCommand;
#endif	/* WHEELVELOCITYCOMMAND_H */

