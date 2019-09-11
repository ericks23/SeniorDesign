
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

void adc_init() {
	//Based off of code from ece 362 lecture notes
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;	//Enable PA timer
	GPIOA->MODER |= GPIO_MODER_MODER4 | GPIO_MODER_MODER5;	//Set PA4 and PA5 to analog
	GPIOA->MODER |= GPIO_MODER_MODER1_0;	//Set PA1 to output
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	//Enable connection between clock and ADC
	RCC->CR2 |= RCC_CR2_HSI14ON;	//Enable high speed clock
	while (!(RCC->CR2 & RCC_CR2_HSI14RDY));	//wait for clock ready
	ADC1->CR |= ADC_CR_ADEN;	//Enable ADC
	while(!(ADC1->ISR & ADC_ISR_ADRDY));	//Wait for ADC to be ready
	while((ADC1->CR & ADC_CR_ADSTART));	//Wait for ADCstart to reset
}

void adc_loop() {
	ADC1->CHSELR = 0;	//unselect all channels
	ADC1->CHSELR |= ADC_CHSELR_CHSEL4;	//select channel 4
	while(!(ADC1->ISR & ADC_ISR_ADRDY));	//Wait for ADC ready
	ADC1-> CR |= ADC_CR_ADSTART;	//Start ADC
	while(!(ADC1->ISR & ADC_ISR_EOC));	//Wait for conversion finish
	if(ADC1->DR < (4095/3)) GPIOA->BSRR = GPIO_BSRR_BS_1;
	else GPIOA->BRR = GPIO_BRR_BR_1;
}
