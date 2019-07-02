#ifndef _DRV_STEPPER_ULN2003_H
#define _DRV_STEPPER_ULN2003_H

#include <stdint.h>

typedef enum _err_stepper_uln2003
{
    OK,
    ERR
} err_stepper_uln2003_t;

typedef enum _stepper_mode
{
    one_phase,
    two_phase,
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
} stepper_uln2003_t;

err_stepper_uln2003_t STEPPER_ULN2003_Init(stepper_uln2003_t *stepper);
err_stepper_uln2003_t STEPPER_ULN2003_DoSteps(stepper_uln2003_t *stepper, uint32_t steps);


#endif // !_DRV_STEPPER_ULN2003_H