#include "manage_interrupt.h"

#ifdef INTERRUPT_PRIORITY_LEVELS
void __interrupt() InterruptManagerHigh(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) &&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        ISR_TMR0();
    }
}

void __interrupt(low_priority) InterruptManagerLow(void)
{  
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) &&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        ISR_TMR0();
    }
}

#else

void  __interrupt() InterruptManager(void)
{   
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) &&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        ISR_TMR0();
    }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
        ISR_TMR1();
    }
}
#endif
