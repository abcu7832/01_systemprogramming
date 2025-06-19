#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}
#if 1
#define BASE  (500) //msec    4분음표 500ms

static void Buzzer_Beep(unsigned char tone, int duration)
{
	const static unsigned short tone_value[] = {261,277,293,311,329,349,369,391,415,440,466,493,523,554,587,622,659,698,739,783,830,880,932,987};

	TIM3_Out_Freq_Generation(tone_value[tone]);
	TIM2_Delay(duration);
	TIM3_Out_Stop();
}

// 4/15 과제2
void Main(void)
{
	Sys_Init();

	int led = 1;
	int n = 0;
	int i = 0;
	int x = 0;
	TIM4_Repeat(1);

	for(;;)
	{
		//UART 값 받기
		if(Macro_Check_Bit_Set(USART1->SR, 5))
		{
			x = Uart_Get_Int_Num();
			Uart_Printf("%d\n", x);
		}
		if(TIM4_Check_Timeout())
		{
			if(n==0)
			{
				led = 0x0;
			}
			else
			{
				if(i==n)
				{
					led ^= 0x1;
				}
				else if(i==10)
				{
					led ^= 0x1;
					i = 0;
				}
				i++;
			}
			if((x!=n)&&((i==0)||(i==1)))
			{
				n = x;
			}
		}
		LED_Display(led);
	}
}
#endif 