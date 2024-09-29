#include "led.h"
Std_ReturnType Led_Init(const led_t *led)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        pin_config_t _pin = {
          .Direction = GPIO_OUTPUT,
          .Logic = led->led_status,
          .Port = led->led_port,
          .Pin = led->led_pin,
        }; 
        ret &= gpio_pin_initialize(&_pin);
    }
    return ret;
}

Std_ReturnType Led_On(const led_t *led)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        pin_config_t _pin = {
          .Direction = GPIO_OUTPUT,
          .Logic = GPIO_HIGH,
          .Port = led->led_port,
          .Pin = led->led_pin,
        }; 
        ret &= gpio_pin_initialize(&_pin);
    }
    return ret;
}

Std_ReturnType Led_Off(const led_t *led)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        pin_config_t _pin = {
          .Direction = GPIO_OUTPUT,
          .Logic = GPIO_LOW,
          .Port = led->led_port,
          .Pin = led->led_pin,
        }; 
        ret &= gpio_pin_initialize(&_pin);
    }
    return ret;
}

Std_ReturnType Led_Toggle(const led_t *led)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        pin_config_t _pin = {
          .Direction = GPIO_OUTPUT,
          .Logic = !(led->led_status),
          .Port = led->led_port,
          .Pin = led->led_pin,
        }; 
        ret &= gpio_pin_initialize(&_pin);
    }
    return ret;
}
