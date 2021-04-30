#include "task.h"


task::task()
{
	task_ID = 0;
	task_time = 10;
	task_com = 10;
	task_prio = 1;
	core_no = 0;
}

task::task(int id, int time, int com, int prio, int core)
{
	task_ID = id;
	task_time = time;
	task_com = com;
	task_prio = prio;
	core_no = core;
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

int task::get_core_no()
{
	return core_no;
}

int task::set_core_no(int no)
{
	core_no = no;
	return 0;
}

int task::set_run_time(int time)
{
	task_time = time;
	return 0;
}

int task::set_com(int com)
{
	task_com = com;
	return 0;
}

int task::set_prio(int prio)
{
	task_prio = prio;
	return 0;
}

int task::set_id(int id)
{
	task_ID = id;
	return 0;
}
