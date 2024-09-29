/*
 * File:   project.c
 * Author: ah427
 *
 * Created on 21 ?????, 2024, 08:41 ?
 */


#include <xc.h>
//#include <builtins.h>
#include "project.h"
#include "ECU/mcal_led/led.h"

#define _XTAL_FREQ 40000000UL

//volatile uint16 tmr_counter = 0;
//volatile uint16 counter = 0;
//void app_timer0(void){
//    counter++;
//}
//
//Timer0_t timer0_counter = {
//    .Timer0_InterruptHandler = app_timer0,
//    .clock_source_mood = TIMER0_COUNTER_MOOD_CFG,
//    .source_edge = TIMER0_RISING_EDGE_CFG,
//    .register_size = TIMER0_16BIT_CFG,
//    .prescaler_mood = TIMER0_PRESCALER_DISABLE_CFG,
//    .preload_data = 0,
//};
//
//void initialization(void);
//void main(void) {
//    initialization();
//    while(1){
//        Timer0_Read(&timer0_counter, &tmr_counter);
//        
//
////        __delay_ms(150); 
////        Timer0_Write(&timer0_counter, 0);
////                tmr_counter = 0;
//    }
//
//    return;
//}

//void initialization(void){  
//    Timer0_Init(&timer0_counter);
//}



volatile uint16 tmr_flag = 0, read_value = 0;
led_t led = {.led_status = GPIO_LOW, .led_port = GPIO_PORTC, .led_pin = GPIO_PIN0};
void app_timer0(void){
    tmr_flag++;
    Led_Toggle(&led);
}

Timer0_t tmr = { // 100ms
    .Timer0_InterruptHandler = app_timer0,
    .clock_source_mood = TIMER0_TIMER_MOOD_CFG,
    .register_size = TIMER0_16BIT_CFG,  
    .prescaler_mood = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = PRESCALER_MOD_4,
    .preload_data = 15536,
};

void initialization(void);
void main(void) {

    initialization();
    Timer0_Read(&tmr, &read_value);
    __delay_ms(150);
     
    return;
}

void initialization(void){  
    Timer0_Init(&tmr);
    Led_Init(&led);
}



//led_t led = {.led_port = GPIO_PORTC, .led_pin = GPIO_PIN0, .led_status = GPIO_HIGH};
//volatile uint16 timer1_on = 0;
//void timer1_DefaultInterruptHandler(void)
//{
//    timer1_on++;
//}

//void timer1_timer_init(void){
////    TRISCbits.TRISC0 = 1;
//    Timer1_t tmr_obj;
//    tmr_obj.Timer1_InterruptHandler = timer1_DefaultInterruptHandler;
//    tmr_obj.timer1_mood = TIMER1_TIMER_MOOD_CFG;
//    tmr_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_4;
//    tmr_obj.timer1_preload_value = 15536;
//    tmr_obj.timer1_reg_rw_mood = TIMER1_RW_REG_16BIT_MOOD;
//    Timer1_Init(&tmr_obj);
//        
//}

//void timer1_counter_init(void){
//    Timer1_t counter_obj;
//    counter_obj.Timer1_InterruptHandler = timer1_DefaultInterruptHandler;
//    counter_obj.timer1_mood = TIMER1_COUNTER_MOOD_CFG;
//    counter_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_1;
//    counter_obj.timer1_preload_value = 0;
//    counter_obj.timer1_reg_rw_mood = TIMER1_RW_REG_8BIT_MOOD;
//    counter_obj.timer1_counter_mood = TIMER1_SYNC_COUNTER_MOOD_CFG;
//    Timer1_Init(&counter_obj);
//}

//void initialization(void);
//volatile uint16 read_value = 0;
//void main(void) {
//
//    initialization();
//    timer1_timer_init();
//    Timer1_Read(&timer1_timer_init, &read_value);
//     
//    return;
//}
//
//void initialization(void){  
////    Led_Init(&led);
//}
