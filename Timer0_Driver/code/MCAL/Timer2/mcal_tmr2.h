/* 
 * File:   mcal_timer2.h
 * Author: ah427
 *
 * Created on 30 ??????, 2024, 07:07 ?
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H


/* SECTION: Include */
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/internal_interrupt.h"

/* SECTION: Macro Declarations */
#define TIMER2_ENABLE_CFG    1
#define TIMER2_DISABLE_CFG   0

/* SECTION: Macro Function Declarations */
#define TIMER2_POSTCALE(_CONFIG)        (T2CONbits.TOUTPS = _CONFIG)
#define TIMER2_ENABLE()                 (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()                (T2CONbits.TMR2ON = 0)
#define TIMER2_PRESCALER(_CONFIG)       (T2CONbits.T2CKPS = _CONFIG)

/* SECTION: Data Type Declarations */
typedef enum{
    TIMER2_POSTCALE_DIV_BY_1= 0,
    TIMER2_POSTCALE_DIV_BY_2,
    TIMER2_POSTCALE_DIV_BY_3,
    TIMER2_POSTCALE_DIV_BY_4,
    TIMER2_POSTCALE_DIV_BY_5,
    TIMER2_POSTCALE_DIV_BY_6,
    TIMER2_POSTCALE_DIV_BY_7,
    TIMER2_POSTCALE_DIV_BY_8,
    TIMER2_POSTCALE_DIV_BY_9,
    TIMER2_POSTCALE_DIV_BY_10,
    TIMER2_POSTCALE_DIV_BY_11,
    TIMER2_POSTCALE_DIV_BY_12,
    TIMER2_POSTCALE_DIV_BY_13,
    TIMER2_POSTCALE_DIV_BY_14,
    TIMER2_POSTCALE_DIV_BY_15,
    TIMER2_POSTCALE_DIV_BY_16, 
}Timer2_Postcale;

typedef enum{
    TIMER2_PRESCALER_DIV_BY_1 = 0,
    TIMER2_PRESCALER_DIV_BY_2,
    TIMER2_PRESCALER_DIV_BY_4,
}Timer2_Prescaler;

typedef struct{
    #ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
        void(*Timer2_InterruptHandler)(void);
        #ifdef INTERRUPT_PRIORITY_LEVELS
            interrupt_priority priority:1;
        #endif
    #endif
    uint8 timer2_preload;
    Timer2_Postcale select_postcale_value;
    Timer2_Prescaler select_prescaler_value;
    uint8 timer2_enable:1;
}Timer2_t;
/* SECTION: Interface Function Declarations */
Std_ReturnType Timer2_Init(const Timer2_t *_tmr);
Std_ReturnType Timer2_DeInit(const Timer2_t *_tmr);
Std_ReturnType Timer2_Read(const Timer2_t *_tmr, uint8 *value);
Std_ReturnType Timer2_Write(const Timer2_t *_tmr, uint8 value);
#endif	/* MCAL_TIMER2_H */

