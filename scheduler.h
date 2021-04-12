#pragma once
#include "math.h"
#include "cpu.h"
#include "task.h"

class schedul
{
private:
	 
public:
	schedul();
	double get_banlance_class(double** p, int n, int m);
	int add_one_task_to_one_core(core c, task* t);
	int add_task_to_one_core(core c, task* p, int n);
	int add_task_to_core(multi_core m_c, int start_core_no, task** p, int core_num, int* n);
	int get_one_core_task(core c, int start_no, int num, task** q);
	int get_core_task(multi_core m_c, );
	int sort_prio();
	int get_cores();
	int select_min_queue();
	int get_height_core();
	int move_task();
	int Linux_load_balance_schedule();
	int DLBQ_load_balance_schedule();
	int Base_load_balance_schedule();
};