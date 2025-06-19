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

void Main(void)
{
	// KEY0,1을 누르면 Tera Term에 키값을 출력 for toggling
	Sys_Init();
	Uart1_Printf("EXTI Test\n");

	// AFIO, Port-B Clock Enable  271p
	Macro_Write_Block(RCC->APB2ENR, 0xf, 0x9, 0);
	// PB[7:6]을 입력으로 선언 
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);
	// PB[7:6]을 EXTI 소스로 설정하고 => B Port
	Macro_Write_Block(AFIO->EXTICR[1], 0xff, 0x11, 8);
	// Falling edge 선택
	Macro_Write_Block(EXTI->FTSR, 0x3, 0x3, 6);
	// EXTI[7:6] Pending Clear(대입연산)
	EXTI->PR = 0x3<<6;
	// EXTI[7:6] 인터럽트 허용
	Macro_Write_Block(EXTI->IMR,0x3,0x3,6);
	// NVIC의 인터럽트 Pending clear
	EXTI9_5_IRQHandler(); //=> stm32f10x_it.c 479th line
	// EXTI9_5 인터럽트 허용
	NVIC_EnableIRQ(23);

	for(;;)
	{
		LED_Display(1);
		TIM2_Delay(500);
		LED_Display(2);
		TIM2_Delay(500);
	}
}
