#include "drv_stepper_uln2003.h"

static void __PopulateStates(stepper_uln2003_t * stepper)
{
    stepper->states_count = 4;

    // TODO clear states
    switch(stepper->mode)
    {
        case one_phase_on:
            stepper->states_count = 4;
            stepper->states[0] = 0x01;
            stepper->states[1] = 0x02;
            stepper->states[2] = 0x04;
            stepper->states[3] = 0x08;
            break;
        
        case two_phase_on:
            stepper->states_count = 4;
            stepper->states[0] = 0x01 | 0x02;
            stepper->states[1] = 0x02 | 0x04;
            stepper->states[2] = 0x04 | 0x08;
            stepper->states[3] = 0x08 | 0x01;
            break;

        case half_stepping:
            stepper->states_count = 8;
            stepper->states[0] = 0x01;
            stepper->states[1] = 0x01 | 0x02;
            stepper->states[2] = 0x02;
            stepper->states[3] = 0x02 | 0x04;
            stepper->states[4] = 0x04;
            stepper->states[5] = 0x04 | 0x08;
            stepper->states[6] = 0x08;
            stepper->states[7] = 0x08 | 0x01;
            break;

        default:
            break;
    }
}

static void __RenewStateIndex(stepper_uln2003_t *stepper) 
{
    int8_t buffer;

    if(stepper->direction == clockwise)
    {
        buffer = stepper->current_state + 1;
    }
    else 
    {
        buffer = stepper->current_state - 1;
    }

    if(buffer < 0) 
    {
        stepper->current_state = stepper->states_count - 1;
        return;
    }

    if(buffer > (stepper->states_count - 1)) 
    {
        stepper->current_state = 0;
        return;
    }

    stepper->current_state = buffer;
}

err_stepper_uln2003_t STEPPER_ULN2003_Init(stepper_uln2003_t *stepper)
{
    err_stepper_uln2003_t ret = OK;

    __PopulateStates(stepper);
    stepper->current_state = 0;

    return ret;
}

void STEPPER_ULN2003_Tick(stepper_uln2003_t *stepper)
{
    stepper->StateWrite(stepper->current_state);
    __RenewStateIndex(stepper);
}

void STEPPER_ULN2003_DoSteps(stepper_uln2003_t *stepper, uint32_t steps)
{
    uint32_t i = 0;
    uint8_t j = 0;

    for(i = 0; i < steps; i++)
    {
        for(j = 0; j < stepper->states_count; j++)
        {
            STEPPER_ULN2003_Tick(stepper);
            stepper->DelayMs(stepper->state_duration);
        }
    }
}