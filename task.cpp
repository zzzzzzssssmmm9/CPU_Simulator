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

int task::get_time()
{
	return task_time;
}

int task::get_com()
{
	return task_com;
}

int task::get_ID()
{
	return task_ID;
}

int task::get_prio()
{
	return task_prio;
}