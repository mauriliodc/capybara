#include "control_algorithm.h"


//PID control
void PIDControlAlgorithm_fn(struct ControlAlgorithm* _ca) {
    struct PIDControlAlgorithm* ca = (struct PIDControlAlgorithm*) _ca;

    ca->_error=ca->_base._input-ca->_base._measure;
    //ca->_error=-ca->_base._measure;
    ca->_Pi=ca->_error*ca->_KP;
    ca->_I+=ca->_KI_times_PERIOD * ca->_error;
    ca->_I=(ca->_I >  ca->_windup)?  ca->_windup  : ca->_I;
    ca->_I=(ca->_I < -ca->_windup) ? -ca->_windup : ca->_I;

    ca->_D = (ca->_error - ca->_previous_error) * ca->_KD_div_PERIOD;
    ca->_previous_error = ca->_error;

    ca->_base._control=(ca->_Pi+ca->_I+ca->_D+ca->_base._input)*ca->_kc;
    
}

//PID init
void PIDControlAlgorithm_init(struct PIDControlAlgorithm* ca, int16_t KP, int16_t KI, int16_t KD, int16_t windup, int16_t period, int16_t kc) {
    ca->_KP = KP;
    ca->_KD = KD;
    ca->_KP = KP;

    ca->_D = 0;
    ca->_I = 0;
    ca->_Pi = 0;

    ca->_period = period;
    ca->_windup = windup;

    ca->_KI_times_PERIOD=KI*period;
    ca->_KD_div_PERIOD = KD/period;
    ca->_error=0;
    ca->_previous_error=0;

    ca->_base._control = 0;
    ca->_base._measure = 0;
    ca->_kc=kc;
    ca->_kc_inverse=1/kc;

    ca->_base._controlFn = &PIDControlAlgorithm_fn;
}

//update step of the control algorithm
int16_t ControlAlgorithm_update(struct ControlAlgorithm* ca, int16_t measure, int16_t input){
    ca->_measure = measure;
    ca->_input = input;
    ca->_controlFn(ca);
    return ca->_control;
}

