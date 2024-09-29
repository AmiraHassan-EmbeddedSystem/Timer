/* 
 * File:   internal_interrupt.h
 * Author: Amira Hassan
 * 
 * Created on 19 / 9 / 2024, 6:33 am
 * 
 * Description: This file contains the initialization and handling functions 
 *              for internal interrupts using the Hardware Abstraction Layer (HAL).
 *              Internal interrupts are triggered by internal peripherals such as timers,
 *              ADCs, or communication modules (e.g., UART, SPI) to handle specific events 
 *              (e.g., timer overflow, data reception).
 *             
 */

#ifndef INTERNAL_INTERRUPT_H
#define	INTERNAL_INTERRUPT_H

/* SECTION: Include */
#include "manage_interrupt.h"

/* SECTION: Macro Declarations */

#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
    #define TIMER0_INTERRUPT_ENABLE()   (INTCONbits.TMR0IE = 1)
    #define TIMER0_INTERRUPT_DISABLE()   (INTCONbits.TMR0IE = 0)
    #define TIMER0_INTERRUPT_CLEAR_FLAG()   (INTCONbits.TMR0IF = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS
    #define TIMER0_INTERRUPT_HIGH_PRIORITY()   (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_LOW_PRIORITY()   (INTCON2bits.TMR0IP = 0)
#endif
#endif

#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    #define TIMER1_INTERRUPT_ENABLE()   (PIE1bits.TMR1IE = 1)
    #define TIMER1_INTERRUPT_DISABLE()   (PIE1bits.TMR1IE = 0)
    #define TIMER1_INTERRUPT_CLEAR_FLAG()   (PIR1bits.TMR1IF = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS
    #define TIMER1_INTERRUPT_HIGH_PRIORITY()   (IPR1bits.TMR1IP = 1)
    #define TIMER1_INTERRUPT_LOW_PRIORITY()   (IPR1bits.TMR1IP = 0)
#endif
#endif

/* SECTION: Macro Function Declarations */
/* SECTION: Data Type Declarations */

/* SECTION: Interface Function Declarations */

#endif	/* INTERNAL_INTERRUPT_H */

