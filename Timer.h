#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "random.h"

class Timer
{
private:
	double Base_Timer;
	double CPU_Timer;
	double IO_Timer;
	double CPU_T_mul;
	double IO_T_mul;
	int T_set();
public:
	Timer();
	Timer(double time, double C_T_M, double I_T_M);
	int T_init();
	int set_timer();
	int run(int modle);
};