#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "clock_config.h"
#include "pin_mux.h"
void delay(void);
 void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 300000; ++i)
    {
        __asm("NOP");
    }
}

int main(void)
{

	static const gpio_pin_config_t LED_configOutput = {

	  kGPIO_DigitalOutput,  /* use as output pin */

	  1,  /* initial value */

	};


    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    GPIO_PinInit(GPIOB, 18U, &LED_configOutput);
    while (1)
    {
    	GPIO_ClearPinsOutput(GPIOB, 1<<18U); /* green led on */
        delay();
        GPIO_SetPinsOutput(GPIOB, 1<<18U);
        delay();

    }
}
