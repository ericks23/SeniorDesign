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
 * PA1 - test output (LED)
 * PA4 - ADC input
 * PA5 - ADC input
 */

#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

#include "ADCcode.h"
			

int main(void)
{
	adc_init();
	while(1) {
		adc_loop();
	}
}
