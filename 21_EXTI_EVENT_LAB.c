#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();

	SCB->VTOR = 0x08003000;
	SCB->SHCSR = 0;
}

extern volatile int Key_Value;

void Main(void)
{
	// KEY0,1을 누르면 Tera Term에 키값을 출력 for toggling
	Sys_Init();
	Uart1_Printf("EXTI KEY ISR Test\n");

	Key_ISR_Enable(1);//=>stm32f10x_it.c 470에 나와있음음

	for(;;)
	{
		if(Key_Value)
		{
			Uart1_Printf("KEY=%d\n", Key_Value);
			Key_Value = 0;
		}

		LED_Display(1);
		TIM2_Delay(500);
		LED_Display(2);
		TIM2_Delay(500);
	}
}
