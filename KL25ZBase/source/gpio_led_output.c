#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include <stdio.h>

static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

static uint8_t txbuff[] = "Lpuart polling example\r\nBoard will send back received characters\r\n";
#define DEMO_LPUART LPUART0
#define DEMO_LPUART_CLKSRC kCLOCK_McgIrc48MClk

static void InitLPUART(void) {
  lpuart_config_t config;

   CLOCK_SetLpuart0Clock(1U);
  /*
   * config.baudRate_Bps = 38400U;
   * config.parityMode = kLPUART_ParityDisabled;
   * config.stopBitCount = kLPUART_OneStopBit;
   * config.txFifoWatermark = 0;
   * config.rxFifoWatermark = 0;
   * config.enableTx = false;
   * config.enableRx = false;
   */
  LPUART_GetDefaultConfig(&config);
  config.baudRate_Bps = 38400;
  config.enableTx = true;
  config.enableRx = true;
  LPUART_Init(DEMO_LPUART, &config, CLOCK_GetFreq(DEMO_LPUART_CLKSRC));
}

bool writable(LPUART_Type *base) {
  return (LPUART_GetStatusFlags(base)&LPUART_STAT_TDRE_MASK)!=0;
}

bool readable(LPUART_Type *base) {
  return (LPUART_GetStatusFlags(base)&LPUART_STAT_RDRF_MASK)!=0;
}

/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
#if 0
  BOARD_InitDebugConsole();
#else
  InitLPUART();
  LPUART_WriteBlocking(DEMO_LPUART, txbuff, sizeof(txbuff) - 1);
#endif

  /* Add your code here */
  for(;;) {
    if (readable(DEMO_LPUART)) {
      uint8_t ch;

      LPUART_ReadBlocking(DEMO_LPUART, &ch, 1);
      if (writable(DEMO_LPUART)) {
        LPUART_WriteBlocking(DEMO_LPUART, &ch, 1);
      }
    }
    /* include <stdio.h>
     * replace -specs=nosys.specs with -specs=rdimon.specs
     * enable semihosting in launch config, route to gdb
     * removed -Xlinker -z -Xlinker muldefs
     * ./utilities/fsl_debug_console.o:C:\tmp\wsp_kds_3.0.0\FRDM-KL27Z_Blinky\Debug/../utilities/fsl_debug_console.c:1702: first defined here
     *
     */
    printf("hello world!\r\n");
    GPIO_ClearPinsOutput(GPIOA, 1<<13u); /* blue led on */
    delay(1000000);
    GPIO_SetPinsOutput(GPIOA, 1<<13u); /* blue led off */
    delay(1000000);

    GPIO_ClearPinsOutput(GPIOB, 1<<18u); /* red led on */
    delay(1000000);
    GPIO_SetPinsOutput(GPIOB, 1<<18u); /* red led off */
    delay(500000);

    GPIO_ClearPinsOutput(GPIOB, 1<<19u); /* green led on */
    delay(1000000);
    GPIO_SetPinsOutput(GPIOB, 1<<19u); /* green led off */
    delay(1000000);
  }
  for(;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP"); /* something to use as a breakpoint stop while looping */
  }
}
