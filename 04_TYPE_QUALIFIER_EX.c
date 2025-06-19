#include "device_driver.h"

#if 0

#define RCC_APB2ENR   (*(unsigned long*)0x40021018)

#define GPIOB_CRH      (*(volatile unsigned long*)0x40010C04)
#define GPIOB_ODR      (*(volatile unsigned long*)0x40010C0C)

void Main(void)
{
	volatile int i;

	Uart_Init(115200);
	Uart_Printf("LED Toggling Test #1\n");
	RCC_APB2ENR |= (1<<3);
	RCC_APB2ENR |= (1<<2);

	GPIOB_CRH = 0x66 << 0;

	for(;;)
	{
		GPIOB_ODR = 0x0 << 8;
		for(i=0; i<0x40000; i++);
		GPIOB_ODR = 0x3 << 8;
		for(i=0; i<0x40000; i++);
	}
}

#endif

#if 01
//과제 4/9
#define RCC_APB2ENR   (*(unsigned long*)0x40021018)

#define GPIOA_CRL      (*(volatile unsigned long*)0x40010800)
#define GPIOA_ODR      (*(volatile unsigned long*)0x4001080C)

void Main(void)
{
	volatile int i;

	Uart_Init(115200);
	Uart_Printf("LED Toggling Test #1\n");
	RCC_APB2ENR |= (1<<3);//PORT B - ON
	RCC_APB2ENR |= (1<<2);//PORT A - ON
	
	GPIOA_CRL = 0x6 << 8;//PA2

	for(;;)
	{
		GPIOA->ODR = 0x0 << 2;
		for(i=0; i<0x40000; i++);
		GPIOA->ODR = 0x1 << 2;
		for(i=0; i<0x40000; i++);
	}
}

#endif

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #1\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #2\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define TIMER   (*(volatile unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #3\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define RCC_APB2ENR   (*(volatile unsigned long*)0x40021018)

#define GPIOB_CRH      (*(volatile unsigned long*)0x40010C04)
#define GPIOB_ODR      (*(volatile unsigned long*)0x40010C0C)

void Main(void)
{
	volatile int i;

	Uart_Init(115200);
	Uart_Printf("LED Toggling Test #2\n");
	RCC_APB2ENR |= (1<<3);

	GPIOB_CRH = 0x66 << 0;

	for(;;)
	{
		GPIOB_ODR = 0x0 << 8;
		for(i=0; i<0x40000; i++);
		GPIOB_ODR = 0x3 << 8;
		for(i=0; i<0x40000; i++);
	}
}

#endif
