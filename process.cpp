#include "process.h"


process::process()
{
	pro_ID = 0;
	thread_num = 1;
}

process::process(int id, int th_num)
{
	pro_ID = id;
	thread_num = th_num;
}