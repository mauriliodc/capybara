/* 
 * File:   control_algorithm.h
 * Author: malcom
 *
 * Created on June 18, 2013, 1:10 PM
 */

#ifndef CONTROL_ALGORITHM_H
#define	CONTROL_ALGORITHM_H
#include "platform_defs.h"

struct ControlAlgorithm;

typedef void (*ControlFn_t) (struct ControlAlgorithm*);


struct ControlAlgorithm {
  int16_t _measure; 
  int16_t _input; 
  int16_t _control; 
  ControlFn_t _controlFn;
};


struct PIDControlAlgorithm{
  struct ControlAlgorithm _base;
  int16_t _KP;
  int16_t _KI;
  int16_t _KD;
  int16_t _windup;
  
  int16_t _Pi;
  int16_t _I;
  int16_t _D;
  int16_t _KI_times_PERIOD; //TODO divisione tra due int?
  int16_t _KD_div_PERIOD;
  int16_t _period;
  int16_t _error;
  int16_t _previous_error;

  int16_t _kc;
  int16_t _kc_inverse; //TODO divisione 1/int?
};

int16_t ControlAlgorithm_update(struct ControlAlgorithm* ca, int16_t measure, int16_t input);
void PIDControlAlgorithm_fn(struct ControlAlgorithm* ca);
void PIDControlAlgorithm_init(struct PIDControlAlgorithm* ca, int16_t KP, int16_t KI, int16_t KD, int16_t windup, int16_t period, int16_t kc);

#endif	/* CONTROL_ALGORITHM_H */

