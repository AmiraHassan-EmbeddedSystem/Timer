/* 
 * File:   mcal_tmr1.h
 * Author: ah427
 *
 * Created on 22 ??????, 2024, 11:57 ?
 */

#ifndef MCAL_TMR1_H
#define	MCAL_TMR1_H

/* SECTION: Include */
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/internal_interrupt.h"

/* SECTION: Macro Declarations */
#define TIMER1_TIMER_MOOD_CFG     0
#define TIMER1_COUNTER_MOOD_CFG   1

#define TIMER1_ASYNC_COUNTER_MOOD_CFG   1
#define TIMER1_SYNC_COUNTER_MOOD_CFG    0

#define TIMER1_OSCILLATOR_ENABLE   1
#define TIMER1_OSCILLATOR_DISABLE   0

#define TIMER1_PRESCALER_DIV_BY_1   0
#define TIMER1_PRESCALER_DIV_BY_2   1
#define TIMER1_PRESCALER_DIV_BY_4   2
#define TIMER1_PRESCALER_DIV_BY_8   3

#define TIMER1_RW_REG_8BIT_MOOD     0
#define TIMER1_RW_REG_16BIT_MOOD     1


/* SECTION: Macro Function Declarations */
#define TIMER1_ENABLE()      (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()     (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MOOD_ENABLE()   (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MOOD_ENABLE() (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MOOD() (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MOOD() (T1CONbits.T1SYNC = 0)

#define TIMER1_OSC_HW_ENABLE()     (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()     (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)   (T1CONbits.T1CKPS = _PRESCALER_)

#define TIMER1_SYSTEM_CLK_STATUS()      (T1CONbits.T1RUN)

#define TIMER1_RW_REG_8BIT_ENABLE()     (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_ENABLE()     (T1CONbits.RD16 = 1)


/* SECTION: Data Type Declarations */



typedef struct{
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    void (*Timer1_InterruptHandler)(void);
    #ifdef INTERRUPT_PRIORITY_LEVELS 
        interrupt_priority priority;
    #endif
#endif
        uint16 timer1_preload_value;
    uint8 timer1_prescaler_value:2; 
    uint8 timer1_mood:1;
    uint8 timer1_counter_mood:1;
    uint8 timer1_osc_cfg:1;               
    uint8 timer1_reg_rw_mood:1;
    uint8 timer1_reseved:2; 
        

}Timer1_t;


/* SECTION: Interface Function Declarations */
Std_ReturnType Timer1_Init(const Timer1_t *_tmr);
Std_ReturnType Timer1_DeInit(const Timer1_t *_tmr);
Std_ReturnType Timer1_Read(const Timer1_t *_tmr, uint16 *value);
Std_ReturnType Timer1_Write(const Timer1_t *_tmr, uint16 value);
#endif	/* MCAL_TMR1_H */

