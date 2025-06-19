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

// extern volatile int Key_Value;
// extern volatile int Uart1_Rx_In;
// extern volatile int Uart1_Rx_Data;
extern volatile int n;

void Main(void)
{//140p 280p
	//int i=0;
	Sys_Init();

	Uart1_RX_Interrupt_Enable(1);
	
	TIM4_Out_Init();
	TIM4_Out_PWM_Generation(1000, 0);

	for(;;)
	{
		Uart1_Printf(".");
		TIM2_Delay(500);
		/*i++;
		if(i==(sizeof(song1)/sizeof(song1[0])))
		{
			i=0;
		}*/
	}
}
