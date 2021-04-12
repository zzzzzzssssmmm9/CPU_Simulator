#include "Timer.h"

Timer::Timer()
{
	Base_Timer = 5000;
	CPU_T_mul = 2;
	IO_T_mul = 5;
	if (T_init())
	{
		exit(0);
	}
}

Timer::Timer(double time, double C_T_M, double I_T_M)
{
	Base_Timer = time;
	CPU_T_mul = C_T_M;
	IO_T_mul = I_T_M;
	if (T_init())
	{
		exit(0);
	}
}

int Timer::T_init()
{
	T_set();
	return 0;
}

int Timer::T_set()
{
	CPU_Timer = Base_Timer * CPU_T_mul;
	IO_Timer = Base_Timer * IO_T_mul;
	return 0;
}

int Timer::set_timer()
{
	int modle;
	random rand;
	printf("input Base Timer model ( 0 ) input/ ( 1 ) random\n");
	scanf("%d", &modle);
	if (modle)
	{
		rand.set_seed();
		Base_Timer = (double)rand.get_random();
	}
	else
	{
		printf("input Base Timer, CPU Time Mul, IO Time Mul\n");
		scanf("%f,%f,%f", &Base_Timer, &CPU_T_mul, &IO_T_mul);
	}
	T_set();
	return 0;
}

int Timer::run(int modle)             //选择时钟运行模式:( 0 ) 基础时钟,( 1 ) CPU时钟, ( 2 ) IO 时钟, ( 3 ) CPU超频时钟
{
	int i;
	switch (modle)
	{
	case 0:                //Base Timer
		for (i = 0; i < Base_Timer; i++);
		break;
	case 1:                //CPU Timer
		for (i = 0; i < CPU_Timer; i++);
		break;
	case 2:                //IO Timer
		for (i = 0; i < IO_Timer; i++);
		break;
	case 3:                //CPU Super Timer
		for (i = 0; i < CPU_Timer * 0.7; i++);
		break;
	case 4:                //4ms, Linux Base Timer
		for (i = 0; i < 1875000; i++);    
	default:
		return 1;
	}
	return 0;
}

