#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

#if 0
void Main(void)
{
	Sys_Init();
	//Uart_Printf("UART Echo-Back Test\n");
	
	// flag check
	while(!Macro_Check_Bit_Set(USART1->SR, 7));
	// DR <- A
	USART1->DR='A';
	// flag check
	while(!Macro_Check_Bit_Set(USART1->SR, 7));
	// DR <- B
	USART1->DR='B';
	// flag check
	while(!Macro_Check_Bit_Set(USART1->SR, 7));
	// DR <- C
	USART1->DR='C';
}
#endif

#if 1
void Main(void)
{
	Sys_Init();
	Uart_Printf("UART Echo-Back Test\n");
	char x;
	for(;;)
	{
		//받은 글자를 다시 UART로 출력한다
		//TX data register empty (1:empty), DR 레지스터에 write하면 자동 clear 
		while(!Macro_Check_Bit_Set(USART1->SR, 5));//수신
		x=USART1->DR;
		/*while(!Macro_Check_Bit_Set(USART1->SR, 7));//송신
		USART1->DR=x;*/
		Uart1_Send_Byte(USART1->DR);
	}
}
#endif