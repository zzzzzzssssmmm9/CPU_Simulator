#include "cpu.h"

int i;
core* p_temp_core;

core::core()
{
	computing_resource = 10;
	state = 0;
}

core::core(int num)
{
	computing_resource = num;
	state = 0;
}

multi_core::multi_core()
{
	core_num = 10;
	state = 0;
	
}

multi_core::multi_core(int num)
{
	core_num = num;
	state = 0;
}