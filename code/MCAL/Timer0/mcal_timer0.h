/* 
 * File:   mcal_timer0.h
 * Author: ah427
 *
 * Created on 21 ??????, 2024, 09:45 ?
 */

#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H

/* SECTION: Include */
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/internal_interrupt.h"
/* SECTION: Macro Declarations */

#define TIMER0_8BIT_CFG     1
#define TIMER0_16BIT_CFG   0

#define TIMER0_TIMER_MOOD_CFG     1
#define TIMER0_COUNTER_MOOD_CFG   0

#define TIMER0_FOLING_EDGE_CFG  1
#define TIMER0_RISING_EDGE_CFG  0

#define TIMER0_PRESCALER_ENABLE_CFG  1
#define TIMER0_PRESCALER_DISABLE_CFG 0


/* SECTION: Macro Function Declarations */
#define TIMER0_ENABLE()     (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()     (T0CONbits.TMR0ON = 0)

#define TIMER0_8BIT_CONFIGURE()   (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_CONFIGURE()   (T0CONbits.T08BIT = 0)

#define TIMER0_TIMER_MOOD() (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MOOD() (T0CONbits.T0CS = 1)

#define TIMER0_FOLING_EDGE()    (T0CONbits.T0SE = 1)
#define TIMER0_RISING_EDGE()    (T0CONbits.T0SE = 0)

#define TIMER0_PRESCALER_ENABLE()   (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()   (T0CONbits.PSA = 1)

#define TIMER0_PRESCALER_VALUE(_VALUE)    (T0CONbits.T0PS = _VALUE)

/* SECTION: Data Type Declarations */

typedef enum{
    PRESCALER_MOD_2= 0,
    PRESCALER_MOD_4,
    PRESCALER_MOD_8,
    PRESCALER_MOD_16,
    PRESCALER_MOD_32,
    PRESCALER_MOD_64,
    PRESCALER_MOD_128,
    PRESCALER_MOD_256,            
}select_prescaler_value;

typedef struct{ 
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
    void (*Timer0_InterruptHandler)(void);
    #ifdef INTERRUPT_PRIORITY_LEVELS 
        interrupt_priority priority;
    #endif
#endif
    uint16 preload_data;
    select_prescaler_value prescaler_value;
    uint8 register_size:1;               // 8BIT OR 16BIT
    uint8 clock_source_mood:1;      // TIMER OR COUNTER
    uint8 source_edge:1;            // RISING OR FOLING
    uint8 prescaler_mood:1;         // ENABLE OR DISABLE
    uint8 reserverd:4;
}Timer0_t;


/* SECTION: Interface Function Declarations */
Std_ReturnType Timer0_Init(const Timer0_t *_tmr);
Std_ReturnType Timer0_DeInit(const Timer0_t *_tmr);
Std_ReturnType Timer0_Read(const Timer0_t *_tmr, uint16 *value);
Std_ReturnType Timer0_Write(const Timer0_t *_tmr, uint16 value);



#endif	/* MCAL_TIMER0_H */

