/*
 * File:   project.c
 * Author: ah427
 *
 * Created on 21 ?????, 2024, 08:41 ?
 */


#include <xc.h>
//#include <builtins.h>
#include "project.h"

#define _XTAL_FREQ 80000000UL

//led_t led = {.led_port = GPIO_PORTD, .led_pin = GPIO_PIN0, .led_status = GPIO_LOW};

volatile uint16 tmr3_counter_count;
void timer3_DefaultInterruptHandler(void)
{
    tmr3_counter_count++;
}

Timer3_t tmr3_counter_obj;
void timer3_timer_init(void){
    tmr3_counter_obj.Timer3_InterruptHandler = timer3_DefaultInterruptHandler;
    tmr3_counter_obj.timer3_mood = TIMER3_COUNTER_MOOD_CFG;
    tmr3_counter_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    tmr3_counter_obj.timer3_preload_value = 0;
    tmr3_counter_obj.timer3_reg_mood = TIMER3_RW_REG_16BIT_MOOD;
    tmr3_counter_obj.timer3_counter_mood = TIMER3_SYNC_COUNTER_MOOD_CFG;
    Timer3_Init(&tmr3_counter_obj);
    
}    
    
volatile uint16 tmr3_read_value = 0;
void main(void) {
    timer3_timer_init();
    while(1){
        Timer3_Read(&tmr3_counter_obj, &tmr3_read_value);
        __delay_ms(150);
    }
    return;
}
