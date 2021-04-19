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
	int get_time();
	int get_com();
	int get_ID();
	int get_prio();
};

struct ttask
{
	task T;
	ttask* p;
};

struct task_queue
{
	ttask T_Q;
	int task_num;
};
