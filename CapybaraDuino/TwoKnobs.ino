#include "mal_comm.h"

//SERIAL STUFF
//=======================================
struct Packet_Decoder pDecoder;
int ascii;
char* pEnd;
struct Packet clientPacket;
char buf[255];
int completeMessage = 0;
//=======================================


#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
Encoder left(2, 3);
Encoder right(21, 20);
char timerInterrupt = 0;
char pid = 0;

//================================
// TIMER 3 is used as debug to compute the cycles needed by some functions
//================================
void TIMER3_init() {
  TCCR3A = 0;
  TCCR3B = 0;
  TCCR3B |= (1 << CS30);
  TCCR3B |= (0 << CS31);
  TCCR3B |= (0 << CS32);
}
//================================
// TIMER 2 and 1 are used for the pwm, i've modified some data to have a not hearable freq
//================================
void TIMER_1_2_init() {
  //SETTING THE PWM TO A DECENT FREQ
  int myEraser = 7;
  TCCR2B &= ~myEraser;
  TCCR1B &= ~myEraser;
  TCCR2B |= 2;
  TCCR1B |= 2;
}

//================================
// TIMER 5 runs at 100ms, at the moment is used for communications
//================================
void TIMER5_init() { //10ms
  cli();
  TCCR5A = 0;
  TCCR5B = 0;
  OCR5A = 1562;
  TCCR5B |= (1 << WGM52);
  TCCR5B |= (1 << CS50);
  TCCR5B |= (1 << CS52);
  TIMSK5 = (1 << OCIE5A);
  sei();
}

//================================
// TIMER 4 is for the PID loop, or basically the scheduler routine
//================================
void TIMER4_init() { //1ms
  cli();
  TCCR4A = 0;
  TCCR4B = 0;
  OCR4A = 156;
  TCCR4B |= (1 << WGM42);
  TCCR4B |= (1 << CS40);
  TCCR4B |= (1 << CS42);
  TIMSK4 = (1 << OCIE4A);
  sei();
}

//PID STUFF
//==========================
typedef float pidType;

pidType PID_input_1 = 0;
pidType PID_measure_1 = 0;
pidType PID_CONTROL_1 = 0;

pidType PID_P_1 = 0;
pidType PID_KP_1 = 1;
pidType PID_I_1 = 0;
pidType PID_D_1 = 0;
pidType PID_KD_divPERIOD_1 = 0;
pidType PID_KI_timesPeriod_1 = 0;

pidType PID_error_1 = 0;
pidType PID_previousError_1 = 0;

pidType PID_input_2 = 0;
pidType PID_measure_2 = 0;
pidType PID_CONTROL_2 = 0;

pidType PID_P_2 = 0;
pidType PID_KP_2 = 1;
pidType PID_I_2 = 0;
pidType PID_D_2 = 0;
pidType PID_KD_divPERIOD_2 = 0;
pidType PID_KI_timesPeriod_2 = 0;

pidType PID_error_2 = 0;
pidType PID_previousError_2 = 0;
//==========================


void PID() {
  PID_error_1 = PID_input_1 - PID_measure_1;
  PID_P_1 = PID_error_1 * PID_KP_1;
  PID_I_1 = PID_KI_timesPeriod_1 * PID_error_1;
  //WINDUP HERE
  PID_D_1 = (PID_error_1 - PID_previousError_1) * PID_KD_divPERIOD_1;
  PID_CONTROL_1 += PID_P_1 + PID_I_1 + PID_D_1;


  PID_error_2 = PID_input_2 - PID_measure_2;
  PID_P_2 = PID_error_2 * PID_KP_2;
  PID_I_2 = PID_KI_timesPeriod_2 * PID_error_2;
  //WINDUP HERE
  PID_D_2 = (PID_error_2 - PID_previousError_2) * PID_KD_divPERIOD_2;
  PID_CONTROL_2 += PID_P_2 + PID_I_2 + PID_D_2;
  /*
  if (PID_CONTROL_2 > 254)PID_CONTROL_2 = 254;
  if (PID_CONTROL_2 < 254)PID_CONTROL_2 = -254;
  if (PID_CONTROL_1 > 254)PID_CONTROL_1 = 254;
  if (PID_CONTROL_1 < 254)PID_CONTROL_1 = -254;
  */
}




void setup() {

  //SERIAL
  initConsts();
  ascii = 1;
  Packet_Decoder_init(&pDecoder, ascii);
  clientPacket.id = Speed_Payload_ID;
  clientPacket.seq = 0;
  clientPacket.speed.leftTick = 10;
  clientPacket.speed.rightTick = 8;
  pEnd = Packet_write(&clientPacket, buf, ascii);
  //

  TIMER5_init();
  TIMER4_init();
  TIMER_1_2_init();

  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(115200);
  Serial.println("Robot Test:");

  PID_input_1 = 0;
  PID_input_2 = 0;

}

ISR(TIMER5_COMPA_vect) {
  timerInterrupt = 1;
}
ISR(TIMER4_COMPA_vect) {
  pid = 1;
}


int p1 = 0;
int p2 = 0;
unsigned int cycles = 0;
void loop() {
  while (Serial.available() > 0) {
    completeMessage = Packet_Decoder_putChar(&pDecoder, Serial.read());
  }
  if (completeMessage) {
    Packet_parse(pDecoder.buffer_start, &clientPacket, ascii);
    PID_input_1 = clientPacket.speed.leftTick;
    PID_input_2 = clientPacket.speed.rightTick;
    completeMessage = 0;
  }

  if (timerInterrupt == 1) {
    clientPacket.speed.leftTick = PID_measure_1;
    clientPacket.speed.rightTick = PID_measure_2;
    pEnd = Packet_write(&clientPacket, buf, ascii);
    char* pStart = buf;
    while (pStart != pEnd) {
    Serial.print(*pStart);
    pStart++;
  }
    timerInterrupt = 0;
  }

  if (pid == 1) {
    PID_measure_1 = left.read();
    left.write(0);
    PID_measure_2 = right.read();
    right.write(0);

    PID();

    TCNT3 = 0;
    _NOP();
    _NOP();
    _NOP();
    _NOP();
    cycles = TCNT3;
    p1 = PID_CONTROL_1;
    p2 = PID_CONTROL_2;
    if (p2 > 0) {
      analogWrite(10, 0);
      analogWrite(9, p2);
    }
    else {
      analogWrite(10, -p2);
      analogWrite(9, 0);
    }
    if (p1 > 0) {
      analogWrite(12, 0);
      analogWrite(11, p1);
    }
    else {
      analogWrite(12, -p1);
      analogWrite(11, 0);
    }

    pid = 0;
  }


}

