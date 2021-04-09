#include "task.h"


task::task()
{
	task_ID = 0;
	task_time = 10;
	task_com = 10;
	task_prio = 1;
}

task::task(int id, int time, int com, int prio)
{
	task_ID = id;
	task_time = time;
	task_com = com;
	task_prio = prio;
}