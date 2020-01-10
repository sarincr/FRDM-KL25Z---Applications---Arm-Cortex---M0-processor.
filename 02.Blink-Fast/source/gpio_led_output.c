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

    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    GPIO_PinInit(GPIOB,18U, &led_config);
    while (1)
    {
        delay();
        GPIO_TogglePinsOutput(GPIOB, 1u << 18U);
    }
}
