#pragma once
#include"process.h"

class task
{
private:
	int task_ID;
	int task_time;
	int task_com;
	int task_prio;
	process * PProc;
public:
	task();
	task(int id, int time, int com, int priority);
};
