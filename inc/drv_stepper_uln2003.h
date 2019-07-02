#ifndef _DRV_STEPPER_ULN2003_H
#define _DRV_STEPPER_ULN2003_H

#include <stdint.h>

#define STEPPER_MAX_STATES  (8)

typedef enum _err_stepper_uln2003
{
    OK,
    ERR
} err_stepper_uln2003_t;

typedef enum _stepper_mode
{
    one_phase_on,
    two_phase_on,
    half_stepping
} stepper_mode_t;

typedef enum _stepper_direction
{
    clockwise,
    counterclockwise
} stepper_direction_t;

typedef struct _stepper_uln2003
{
    stepper_mode_t mode;
    stepper_direction_t direction;
    uint32_t states[STEPPER_MAX_STATES];
    uint8_t current_state;
    uint8_t states_count;
    uint32_t state_duration;
    // Pointers to expternal functions
    void (*StateWrite)(uint32_t state);  
    void (*DelayMs)(uint32_t ms);
} stepper_uln2003_t;

err_stepper_uln2003_t STEPPER_ULN2003_Init(stepper_uln2003_t *stepper);
void STEPPER_ULN2003_Tick(stepper_uln2003_t *stepper);
void STEPPER_ULN2003_DoSteps(stepper_uln2003_t *stepper, uint32_t steps);

#endif // !_DRV_STEPPER_ULN2003_H