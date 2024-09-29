#include "mcal_timer0.h"

#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
static void (*InterruptHandler)(void) = NULL;
#endif

static uint16 timer0_preload = 0;

static inline Std_ReturnType timer0_prescaler_config(const Timer0_t *_tmr);
static inline Std_ReturnType timer0_mood_select(const Timer0_t *_tmr);
static inline Std_ReturnType timer0_register_select_mood(const Timer0_t *_tmr);



Std_ReturnType Timer0_Init(const Timer0_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        TIMER0_DISABLE();
        ret &= timer0_prescaler_config(_tmr);
        ret &= timer0_mood_select(_tmr);
        timer0_register_select_mood(_tmr);
        TMR0H = (_tmr->preload_data) >> 8;
        TMR0L = (uint8)(_tmr->preload_data);
        timer0_preload = _tmr->preload_data;
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
        InterruptHandler = _tmr->Timer0_InterruptHandler;
    #ifdef INTERRUPT_PRIORITY_LEVELS 
        Interrupt_priorityLevelEnable();
        if(LOW_PRIORITY == _tmr->priority){
            TIMER0_INTERRUPT_LOW_PRIORITY();
            Interrupt_LowPriorityEnable();
        }
        else if(HIGH_PRIORITY == _tmr->priority){
            TIMER0_INTERRUPT_HIGH_PRIORITY();
            Interrupt_HighPriorityEnable();
        }
    #else
        Interrupt_globalInterruptEnable();
        Interrupt_prepheralInterruptEnable();
    #endif
#endif
        TIMER0_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer0_DeInit(const Timer0_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        TIMER0_DISABLE();
    #ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
        TIMER0_DISABLE();
    #endif
    }
    return ret;
}


Std_ReturnType Timer0_Read(const Timer0_t *_tmr, uint16 *value)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 tmr_low = 0, tmr_high = 0;
    if((NULL == _tmr) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        tmr_low = TMR0L;
        tmr_high = TMR0H;
        *value = (uint16)((tmr_high << 8) + (tmr_low));
        
    }
    return ret;
}

Std_ReturnType Timer0_Write(const Timer0_t *_tmr, uint16 value)
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

static inline Std_ReturnType timer0_prescaler_config(const Timer0_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        if(TIMER0_PRESCALER_ENABLE_CFG == _tmr->prescaler_mood){
            TIMER0_PRESCALER_ENABLE();
            TIMER0_PRESCALER_VALUE(_tmr->prescaler_value);
        }
        else if(TIMER0_PRESCALER_DISABLE_CFG == _tmr->prescaler_mood){
            TIMER0_PRESCALER_DISABLE();
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}

static inline Std_ReturnType timer0_mood_select(const Timer0_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else if(TIMER0_TIMER_MOOD_CFG == _tmr->clock_source_mood){
        ret = E_OK;
        TIMER0_TIMER_MOOD();
        }
    else if(TIMER0_COUNTER_MOOD_CFG == _tmr->clock_source_mood){
        ret = E_OK;
        TIMER0_COUNTER_MOOD();
        if(TIMER0_FOLING_EDGE_CFG == _tmr->source_edge){
            TIMER0_FOLING_EDGE();
        }
        else if(TIMER0_RISING_EDGE_CFG == _tmr->source_edge){
            TIMER0_RISING_EDGE();
        }
        else{
            /*Nothing*/
            ret = E_NOT_OK;
        }
    }
    else{
        /*Nothing*/
        ret = E_NOT_OK;
    }
    return ret;
}

static inline Std_ReturnType timer0_register_select_mood(const Timer0_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        if(TIMER0_8BIT_CFG == _tmr->register_size){
            TIMER0_8BIT_CONFIGURE();
        }
        else if(TIMER0_16BIT_CFG == _tmr->register_size){
            TIMER0_16BIT_CONFIGURE();
        }
        else{
            /*Nothing*/
            ret = E_NOT_OK;
        }
    }
    return ret;
}

#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
void ISR_TMR0(void)
{
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = timer0_preload >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(InterruptHandler){
        InterruptHandler();
    }
}
#endif