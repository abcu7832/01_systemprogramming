#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
}

/* Key 인식 */

#if 0

void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Test #1\n");

	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 0);

	for(;;)
	{
		// KEY0이 눌렸으면 LED0를 ON, 안 눌렸으면 OFF
		// Macro_Write_Block(GPIOB->ODR, 0x3, (GPIOB->IDR>>6) & 0x3, 8);
		//~(GPIOB->IDR>>6)&0x1
		if(Macro_Check_Bit_Clear(GPIOB->IDR, 6))//누른경우
		{
			Macro_Clear_Bit(GPIOB->ODR, 8);
		}
		else
		{
			Macro_Set_Bit(GPIOB->ODR, 8);
		}
		// KEY1이 눌렸으면 LED1를 ON, 안 눌렸으면 OFF
		if(Macro_Check_Bit_Clear(GPIOB->IDR, 7))
		{
			Macro_Clear_Bit(GPIOB->ODR, 9);
		}
		else
		{
			Macro_Set_Bit(GPIOB->ODR, 9);
		}
	}
}

#endif

/* Key에 의한 LED Toggling */

#if 0
// 4/10 과제
void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Toggling #1\n");

	int i=0;
	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 0);
	Macro_Set_Bit(GPIOB->ODR, 8);

	for(;;)
	{
		// KEY0가 눌릴때마다 LED0의 값을 Toggling
		if((i!=0)&&(~(GPIOB->IDR>>6)&0x1)){Macro_Invert_Bit(GPIOB->ODR, 8); i=0;}
		else if((i==0)&&((GPIOB->IDR>>6)&0x1)){i=1;}
	}
}

#endif

/* Key에 의한 LED Toggling */

#if 0                                                
// 4/10 과제
void Main(void)
{
	Sys_Init();
	Uart_Printf("KEY Input Toggling #1\n");
	Macro_Set_Bit(RCC->APB2ENR, 2);//PA3사용
	int i=0;
	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOA->CRL, 0xf, 0x8, 12);
	Macro_Set_Bit(GPIOA->ODR, 3);//PA3풀업
	Macro_Set_Bit(GPIOB->ODR, 8);//초기상태 LED

	//
	for(;;)
	{
		if((i!=0)&&Macro_Check_Bit_Clear(GPIOA->IDR, 3)){Macro_Invert_Bit(GPIOB->ODR, 8); i=0;}
		else if((i==0)&&Macro_Check_Bit_Set(GPIOA->IDR, 3)){i=1;}
	}
}

#endif