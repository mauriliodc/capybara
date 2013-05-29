/* 
 * File:   encoderController.h
 * Author: malcom
 *
 * Created on May 29, 2013, 6:07 PM
 */

#ifndef ENCODERCONTROLLER_H
#define	ENCODERCONTROLLER_H

struct _encoder
{
    unsigned int* tickPerQuantum;
    
};

struct encoderController{
    
    struct _encoder* enc1;
    struct _encoder* enc2;
};

#endif	/* ENCODERCONTROLLER_H */

