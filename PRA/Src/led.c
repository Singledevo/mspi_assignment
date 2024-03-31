/*
 * led.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Nilesh
 */

#include "led.h"
#include "stm32f4xx.h"


void LEDInit(uint32_t pin)
{
	//enable gpio clock (in AHB1ENR)
	RCC->AHB1ENR |= BV (LED_GPIO_EN);
	//SET GPIO PIN AS OUTPUT (in MODER)
    LED_GPIO->MODER &= ~BV(pin *2+1)| BV(pin * 2);
    //SET GPIO PIN SPEED TO LOW (in OSPEEDER)
    LED_GPIO->OSPEEDR &= ~(BV(pin *2)|BV(pin *2+1));
    // GET PIN NO PULL PULL UP NO PULL DOWN
    LED_GPIO->PUPDR &= ~(BV(pin *2)| BV(pin *2+1));
    //SET PIN TYPE PUSH-PULL(in OTYPER)
    LED_GPIO->OTYPER &= ~BV(pin);
}
void LEDOn(uint32_t pin)
{
	//set led pin (in ODR)
	LED_GPIO->ODR |= BV(pin);
}

void LEDOff(uint32_t pin)
{
	//clear led pin (in IDR)
	LED_GPIO->IDR &= ~BV(pin);
}

void LEDBlink(uint32_t pin, uint32_t delay)
{
	LEDOn(pin);
	DelayMs(delay);
	LEDOff(pin);
}
