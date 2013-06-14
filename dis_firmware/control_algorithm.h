#ifndef _CONTROL_ALGORITHM_H_
#define _CONTROL_ALGORITHM_H_

struct ControlAlgorithm;

typedef void(*ControlFn_t)(ControlAlgorithm*);

struct ControlAlgorithm {
  uint16_t _measure; // read the input
  uint16_t _control; // read the input
  ControlFn_t _controlFn;
};

struct PIDControlAlgorithm{
  struct ControlAlgorithm _base;
  uint16_t _KP, _KI, _KD, _windup;
  uint16_t _P, _I, _D;
};

void PIDControlAlgorithm_fn(ControlAlgorithm* ca);
void PIDControlAlgorithm_init(PIDControlAlgorithm* ca, int16_t KP, int16_t KI, int16_t KD, int16_t windup, int16_t period);


#endif
