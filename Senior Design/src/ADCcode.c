
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

void adc_init() {
	//Based off of code from ece 362 lecture notes
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER4 | GPIO_MODER_MODER5;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CR2 |= RCC_CR2_HSI14RDY;
	while (! (RCC->CR2 & RCC_CR2_HSI14RDY));
	ADC1->CR |= ADC_CR_ADEN;
	while(! (ADC1->ISR & ADC_ISR_ADRDY));
	while((ADC1->CR & ADC_CR_ADSTART));
}

void adc_loop() {
	ADC1->CHSELR = 0;
	ADC1->CHSELR |= ADC_CHSELR_CHSEL4;
	while(!(ADC1->ISR & ADC_ISR_ADRDY));
	ADC1-> CR |= ADC_CR_ADSTART;
	while(!(ADC1->ISR & ADC_ISR_EOC));
	//sprintf(line, "PA4: %2.2f", ADC1->DR * 3 / 4095.0);
}

void adc_calibrate() {
	//ADC calibration; this code block is from STM32 reference manual
	/* (1) Ensure that ADEN = 0 */
	/* (2) Clear ADEN by setting ADDIS*/
	/* (3) Clear DMAEN */
	/* (4) Launch the calibration by setting ADCAL */
	/* (5) Wait until ADCAL=0 */
	if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
	{
	 ADC1->CR |= ADC_CR_ADDIS; /* (2) */
	}
	while ((ADC1->CR & ADC_CR_ADEN) != 0)
	{
	/* For robust implementation, add here time-out management */
	}
	ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN; /* (3) */
	ADC1->CR |= ADC_CR_ADCAL; /* (4) */
	while ((ADC1->CR & ADC_CR_ADCAL) != 0) /* (5) */
	{
	 //Add time-out management here
	}
	return;
}
void adc_enable() {
	//Enable the ADC. This is also mostly from the reference manual
	/* (1) Ensure that ADRDY = 0 */
	/* (2) Clear ADRDY */
	/* (3) Enable the ADC */
	/* (4) Wait until ADC ready */
	if ((ADC1->ISR & ADC_ISR_ADRDY) != 0) /* (1) */
	{
	 ADC1->ISR |= ADC_ISR_ADRDY; /* (2) */ //Fixed typo on this line, said CR instead of ISR
	}
	//If this does not work, remember that ADEN cannot be enabled for 4 ADC clock cycles after
	//ADCAL is reset to 0.
	ADC1->CR |= ADC_CR_ADEN; /* (3) */
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (4) */
	{
	 //timeout handler here
	}
}
void adc_select_clock() {
	/* This code selects the HSI14 as clock source. */
	/* (1) Enable the peripheral clock of the ADC */
	/* (2) Start HSI14 RC oscillator */
	/* (3) Wait HSI14 is ready */
	/* (4) Select HSI14 by writing 00 in CKMODE (reset value) */
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; /* (1) */
	RCC->CR2 |= RCC_CR2_HSI14ON; /* (2) */
	while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) /* (3) */
	{
	 /* For robust implementation, add here time-out management */
	}
	//ADC1->CFGR2 &= (~ADC_CFGR2_CKMODE); /* (4) */
}
