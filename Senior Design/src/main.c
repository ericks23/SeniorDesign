/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


/*
 * Pins in use:
 * PA4 - ADC input
 * PA5 - ADC input
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "snippets.c"
			

int main(void)
{
	char line[21];

	//Based off of code from ece 362 lecture notes
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER4 | GPIO_MODER_MODER5;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CR2 |= RCC_CR2_HSI14RDY;
	while (! (RCC->CR2 & RCC_CR2_HSI14RDY));
	ADC1->CR |= ADC_CR_ADEN;
	while(! (ADC1->ISR & ADC_ISR_ADRDY));
	while((ADC1->CR & ADC_CR_ADSTART));
	while(1) {
		ADC1->CHSELR = 0;
		ADC1->CHSELR |= ADC_CHSELR_CHSEL4;
		while(!(ADC1->ISR & ADC_ISR_ADRDY));
		ADC1-> CR |= ADC_CR_ADSTART;
		while(!(ADC1->ISR & ADC_ISR_EOC));
		//sprintf(line, "PA4: %2.2f", ADC1->DR * 3 / 4095.0);
	}
}




}
