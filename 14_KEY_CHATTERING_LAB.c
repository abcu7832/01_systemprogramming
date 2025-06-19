#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

void Main(void)
{
	Sys_Init();
	Macro_Set_Bit(RCC->APB2ENR, 2);//PA3사용
	Macro_Write_Block(GPIOA->CRL, 0xf, 0x8, 12);
	Macro_Set_Bit(GPIOA->ODR, 3);//PA3풀업
	Macro_Set_Bit(GPIOB->ODR, 8);//초기상태 LED

	int i = 0;

	for(;;)
	{
		volatile int j;
		
		Uart_Printf("Chattering 제거 방식 Key_Get_Pressed() 동작 시험\n");

		for(;;)
		{
			int k;

			if(((k = Key_Get_Pressed()) != 0) && (i != 0))
			{//k에 저장하고 k값이 0이 아닌지 판별하는 조건
				i=0;
				Uart_Printf("Key Pressed! => [%d]\n", k);
				Macro_Invert_Bit(GPIOB->ODR, 8);
				Key_Wait_Key_Released();
			}
			else
			{
				i=1;
				Uart_Printf("#\n");
				for(j=0; j<0x80000; j++);
			}
		}
	}
}