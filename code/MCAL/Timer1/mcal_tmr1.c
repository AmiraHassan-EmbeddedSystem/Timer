#include "mcal_tmr1.h"

#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
static void (*InterruptHandler)(void) = NULL;
#endif

static uint16 timer1_preload = 0;
static inline void timer1_mood_select(const Timer1_t *_tmr);

Std_ReturnType Timer1_Init(const Timer1_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        TIMER1_PRESCALER_SELECT(_tmr->timer1_prescaler_value);
        timer1_mood_select(_tmr);
        TMR1H = (_tmr->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_tmr->timer1_preload_value);
        timer1_preload = _tmr->timer1_preload_value;
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        InterruptHandler = _tmr->Timer1_InterruptHandler;
    #ifdef INTERRUPT_PRIORITY_LEVELS 
        Interrupt_priorityLevelEnable();
        if(LOW_PRIORITY == _tmr->priority){
            TIMER1_INTERRUPT_LOW_PRIORITY();
            Interrupt_LowPriorityEnable();
        }
        else if(HIGH_PRIORITY == _tmr->priority){
            TIMER1_INTERRUPT_HIGH_PRIORITY();
            Interrupt_HighPriorityEnable();
        }
    #else
        Interrupt_globalInterruptEnable();
        Interrupt_prepheralInterruptEnable();
#endif
#endif        
        TIMER1_ENABLE();
        ret = E_OK; 
    }
    return ret;
}


Std_ReturnType Timer1_DeInit(const Timer1_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK; 
         TIMER1_DISABLE();
    #ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
        TIMER1_DISABLE();
     #endif
    }
    return ret;
}


Std_ReturnType Timer1_Read(const Timer1_t *_tmr, uint16 *value)

{
    Std_ReturnType ret = E_NOT_OK;
    uint8 tmr_low = 0, tmr_high = 0;
    if((NULL == _tmr) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
       ret = E_OK;
        tmr_low = TMR1L;
        tmr_high = TMR1H;
        *value = (uint16)((tmr_high << 8) + tmr_low);
    }
    return ret;
}


Std_ReturnType Timer1_Write(const Timer1_t *_tmr, uint16 value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK; 
        TMR0H = (value) >> 8;
        TMR0L = (uint8)(value);
    }
    return ret;
}

void ISR_TMR1(void)
{
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (uint8)(timer1_preload);
    if(InterruptHandler){
        InterruptHandler();
    }
}


static inline void timer1_mood_select(const Timer1_t *_tmr)
{
    if(TIMER1_TIMER_MOOD_CFG == _tmr->timer1_mood){
        TIMER1_TIMER_MOOD_ENABLE();
        }
    else if(TIMER1_COUNTER_MOOD_CFG == _tmr->timer1_mood){
        TIMER1_COUNTER_MOOD_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MOOD_CFG == _tmr->timer1_counter_mood){
            TIMER1_ASYNC_COUNTER_MOOD();
        }
        else if(TIMER1_SYNC_COUNTER_MOOD_CFG == _tmr->timer1_counter_mood){
            TIMER1_SYNC_COUNTER_MOOD();
        }
        else{
            /*Nothing*/
        }
    }
    else{
        /*Nothing*/
     }
}