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
	int i;
	Sys_Init();
	Uart1_Printf("TIM2 stopwatch test\n");

	for(i=1; i<=10; i++)
	{
		LED_Display(i%4);
		TIM2_Stopwatch_Start();
		SysTick_Run(100*i);
		while(!SysTick_Check_Timeout());
		SysTick_Stop();
		Uart1_Printf("[%d] Elapsed Time = %f msec\n", i, TIM2_Stopwatch_Stop()/1000.);
		// 계산된 time 값을 리턴(단위는 usec) => 천으로 나눈 이유
	}
}

#endif

#if 0

void Main(void)
{
	Sys_Init();
	Uart1_Printf("TIM2 delay test\n");

	for(;;)
	{
		LED_Display(0x1);
		TIM2_Delay(1000);
		LED_Display(0x2);
		TIM2_Delay(1000);
		Uart1_Printf(".");
	}
}

#endif

#if 0

void Main(void)
{
	Sys_Init();
	Uart1_Printf("TIM2 delay test\n");
	int led = 1;
	
	TIM2_Delay2(100);

	for(;;)
	{
		//LED 100ms마다 toggle
		// 평소에 .은 계속 짝고
		//timeout돼야 led toggle
		if(TIM2_Check_Timeout())
		{
			LED_Display(led^=0x1);
			TIM2_Delay2(100);
		}
		Uart1_Printf(".");
	}
}

#endif

#if 0

void Main(void)
{
	int i = 1;

	Sys_Init();
	Uart1_Printf("TIM4 repeat timeout test\n");

	TIM4_Repeat(500);//0.5s마다 반복
	SysTick_Run(500);//

	for(;;)
	{
		if(TIM4_Check_Timeout())
		{
			LED_Display(i%4);
			Uart1_Printf("Timer4 [%d]\n", i++);
			if(i>40) TIM4_Stop();
		}

	    if(SysTick_Check_Timeout())
	    {
			Uart1_Printf("SysTick [%d]\n", i++);
			if(i>40) SysTick_Stop();
	    }
	}
}

#endif

#if 0

void Main(void)
{
	int i = 1;
	// ARR값에 변화를 주어 타이머의 카운트속도를 조절하는 코드
	Sys_Init();

	Uart1_Printf("TIM4 variable interval test\n");

	TIM4_Repeat(50);
	// 처음엔 빨랐다가 느려지고를 i 20의 배수마다 반복
	for(;;)
	{
		if(TIM4_Check_Timeout())
		{
			LED_Display(i%4);
			Uart1_Printf("[%d]", i++);//1씩 증가하여 프린트
			if(i>20) i = 1;//20 넘어가면 1로 초기화
			TIM4_Change_Value(50 * i);//50*i만큼 딜레이됨.
		}
	}
}

#endif

#if 0
// 0415 과제1
#define cycle (int)(100 / 2)

void Main(void)
{
	Sys_Init();
	
	int led = 0;
	int n = 1;
	int i = 0;
	int s = 0;

	TIM4_Repeat(cycle);

	for(;;)
	{
		//UART 값 받기
		if(Uart1_Get_Pressed())
		{
			n = Uart1_Get_Pressed() - '0';
			Uart_Printf("\n %d \n", n);
		}
		if(TIM4_Check_Timeout())
		{
			if(n == 0)
			{
				led = 0x0;
				s=0;
			}				
			else // 0 이외
			{
				if(s == n)// cycle (50ms) 마다 toggle
				{
					led ^= 0x1;
					s = 0;
				}
				s++;
			}
			// 100ms마다 .프린트
			if(i == 10)
			{
				Uart1_Printf(".");
				i = 0;
			}
			i++;
		}
		LED_Display(led);
	}
}
#endif

#if 01
#define FREQUENCY 1000 // 1kHz
// 0415 과제2

void Main(void)
{
	Sys_Init();

	int led = 1;
	int n = 1;
	int i = 0;

	TIM4_Repeat(1);

	for(;;)
	{
		//UART 값 받기
		if(Uart1_Get_Pressed())
		{
			n = USART1->DR - '0';
			Uart_Printf("\n %d \n", n);
		}
		
		if(TIM4_Check_Timeout())// 1ms마다
		{
			if(n == 0)
			{
				led = 0x0;
			}				
			if(i == n)
			{
				led ^= 0x1;
			}
			if(i == 10)// 10ms=>주기기
			{
				led ^= 0x1;
				i = 0;
			}
			i++;
		}
		LED_Display(led);
	}
}
	#endif
