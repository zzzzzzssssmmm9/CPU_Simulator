#pragma once
#include "scheduler.h"
#include <iostream>
#include <Windows.h>
using namespace std;

class sys
{
private:
	schedule sche;
	multi_core m_c_1, m_c_2, m_c_3;
	core c;
public:
	sys();
	int run();
	int create_multi_core(int core_num, int com, double height_state);
	int allo_task_to_core(task** p_1, task** p_2, task** p_3, int task_num, int* height_core_no, int height_core_num, int core_com);
	int check_is_height_core(int* height_core_no, int height_core_num, int no);
	int create_task(int num, int run_time, int com, task** p);
	int create_one_task(task* p, int run_time, int com, int prio, int task_no);
	int get_all_task_com(task** p, int task_num);
	int get_one_core_all_task_run_time(core* c, double* re_time);
	int compare_multi_core_run_time();
	int get_LBD();
	int load_balance(int core_num, int height_num, int* height_core_no, double height_state, int task_run_time, int task_com, int task_grad, int task_num_modle, int t_n);
};