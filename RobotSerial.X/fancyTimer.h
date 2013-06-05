/* 
 * File:   fancyTimer.h
 * Author: Malcom
 *
 * Created on 28 maggio 2013, 19.30
 */

#ifndef FANCYTIMER_H
#define	FANCYTIMER_H

struct timerEvent{
    // durations in millisecs
    int millisecs;
    // -1 = loop
    //  1 = one time
    //  n = how many times trigger the event
    int repetitions;
    void (*callback)(void);
    int executeNow;
    int runInHandler;
};

struct timerController
{
    struct timerEvent** timerEventsArray;
    int millisecsStash;
    int events;
};



void triggerEvent(struct timerController* t)
{
    int i=0;
    //increment the millisecs accumulator
    t->millisecsStash++;
    //eventually reset the millisecs accumulator
    if(t->millisecsStash==10000) t->millisecsStash=0;
    //check for each event in the list which one has to be triggered
    for(i=0;i<t->events;i++)
    {
        //execute the event if the modulo between the millisecs accumulator is zero
        if(t->millisecsStash % t->timerEventsArray[i]->millisecs==0)
        {
            //check if the event has to be executed
            if(t->timerEventsArray[i]->repetitions!=0)
            {
                if (t->timerEventsArray[i]->runInHandler){
                    t->timerEventsArray[i]->callback();
                    //if is not a recurrent event, decrement his counter
                    if(t->timerEventsArray[i]->repetitions!=-1) t->timerEventsArray[i]->repetitions--;
                } else
                    t->timerEventsArray[i]->executeNow = 1;
            }
        }
    }
   
}

void handleTimerEvents(struct timerController* t)
{
    int i=0;
    for(i=0;i<t->events;i++){
        if(t->timerEventsArray[i]->repetitions!=0) {
            if (!t->timerEventsArray[i]->runInHandler){
                t->timerEventsArray[i]->executeNow = 0;
                t->timerEventsArray[i]->callback();
            }
        }
    }

}

//******************************************************************************
//******************************************************************************
struct timerController bigTimer;
struct timerEvent anEvent;
struct timerEvent ledEvent;
struct timerEvent enc1Event;
struct timerEvent enc2Event;
struct timerEvent pidUpdateEvent;
#endif	/* FANCYTIMER_H */

