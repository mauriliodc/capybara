#include <p33Fxxxx.h>
#include "generic_utils.h"
#include "defines.h"

//LED TOGGLING FUCTIONS
//------------------------------------------------------------------------------
void toggleLed1() {
    if (LED1)LED1 = 0;
    else if (LED1 == 0)LED1 = 1;
}

void toggleLed2() {
    if (LED2 == 1)LED2 = 0;
    else if (LED2 == 0)LED2 = 1;
}


//BLOCKING DELAY FUNCTIONS
//------------------------------------------------------------------------------
void DelayN10us(int n) 
{
    int DelayCount;
    for (DelayCount = 0; DelayCount < (57 * n); DelayCount++);
}

void DelayN1ms(int n) {
    int ms;
    for (ms = 0; ms < n; ms++) {
        DelayN10us(100);
    }
}

void DelayN1s(int n)
{
    int s;
    for (s = 0; s < n; s++) {
        DelayN1ms(1000);
    }
}