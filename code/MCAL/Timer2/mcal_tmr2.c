#include "mcal_tmr2.h"
#include <stdlib.h>
void (*tmr_InterruptHandler)(void) = NULL;
void ISR_TMR2(void);

uint8 preload_data = 0;
Std_ReturnType Timer2_Init(const Timer2_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ret){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        TIMER2_DISABLE();
        TIMER2_POSTCALE(_tmr->select_postcale_value);
        TIMER2_PRESCALER(_tmr->select_prescaler_value);
        preload_data = _tmr->timer2_preload;
        TMR2 = _tmr->timer2_preload;
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
        tmr_InterruptHandler = _tmr->Timer2_InterruptHandler;
    #ifdef INTERRUPT_PRIORITY_LEVELS
            Interrupt_priorityLevelEnable();
            if(HIGH_PRIORITY == _tmr->priority){
                Interrupt_HighPriorityEnable();
                TIMER2_INTERRUPT_HIGH_PRIORITY();
            }
            else if(LOW_PRIORITY == _tmr->priority){
                Interrupt_LowPriorityEnable();
                TIMER2_INTERRUPT_LOW_PRIORITY();
            }
            else{
                /*Nothing*/
            }
    #else
            Interrupt_globalInterruptEnable();
            Interrupt_prepheralInterruptEnable();
    #endif
#endif
        TIMER2_ENABLE();

    }
    return ret;
    
}


Std_ReturnType Timer2_DeInit(const Timer2_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ret){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        TIMER2_DISABLE();
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
        TIMER2_DISABLE();
#endif
    }
    return ret;
}


Std_ReturnType Timer2_Read(const Timer2_t *_tmr, uint8 *value)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == ret) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        *value = TMR2;
        ret = E_OK;
    }
    return ret;
}


Std_ReturnType Timer2_Write(const Timer2_t *_tmr, uint8 value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ret){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = value;
        ret = E_OK;
    }
    return ret;
}

void ISR_TMR2(void){
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TMR2 = preload_data;
    if(tmr_InterruptHandler){
        tmr_InterruptHandler();
    }
}