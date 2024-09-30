/* 
 * File:   led.h
 * Author: ah427
 *
 * Created on 22 ??????, 2024, 10:00 ?
 */

#ifndef LED_H
#define	LED_H

/* SECTION: Include */
#include "../../MCAL/GPIO/hal_gpio.h"

/* SECTION: Macro Declarations */
#define LED_ON  1
#define LED_OFF 0
/* SECTION: Macro Function Declarations */
/* SECTION: Data Type Declarations */
typedef struct{
//    pin_config_t pin;
    uint8 led_port;
    uint8 led_pin;
    uint8 led_status:1;
}led_t;
/* SECTION: Interface Function Declarations */
Std_ReturnType Led_Init(const led_t *led);
Std_ReturnType Led_On(const led_t *led);
Std_ReturnType Led_Off(const led_t *led);
Std_ReturnType Led_Toggle(const led_t *led);

#endif	/* LED_H */

