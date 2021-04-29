#pragma once
#include "math.h"
#include "cpu.h"
#include "task.h"

class schedule
{
private:
	int model;                   //CPU运行模式( 0 ) - 单核, ( 1 ) - 多核
	
public:
	schedule();
	schedule(int m);
	int set_modle(int m);
	double get_banlance_class(double** p, int n, int m);    //获得负载均衡度
	int add_one_task_to_one_core(core c, task* t);
	int add_task_to_one_core(core c, task* p, int n);
	int add_task_to_core(multi_core m_c, int start_core_no, task** p, int core_num, int* n);
	int get_one_core_task(core c, int start_no, int num, task** q);
	int get_core_task(multi_core m_c, int core_start_no, int core_num, task*** p, int* task_start_no, int* num);
	int get_one_core_all_task(multi_core m_c, int core_no, task** q, int* re_task_num);
	int get_core_all_task(multi_core m_c, int* core_no, int get_core_num, task*** q, int** task_num);
	int get_all_core_all_task(multi_core m_c, int* re_core_num, task*** q, int** task_num);
	int get_task_queue(multi_core m_c, int* core_no, int get_core_num, task*** q, int** task_num);
	int sort_prio(task** p,int task_num);
	int get_task_pp(task*** q, int** task_num, int core_num, task** p, int* task_n);
	int get_cores(multi_core m_c, multi_core** re_m_c);
	int select_min_queue(task** p1, task** p2, task** p3, task** p4, int task_1_num, int task_2_num, int task_3_num, int task_4_num);
	int select_min_queue_2(task** p1, task** p2, int task_1_num, int task_2_num);
	int select_min_queue_3(task** p1, task** p2, task** p3, int task_1_num, int task_2_num, int task_3_num);
	int get_queue_run_time(task** p, int task_num, int* re_run_time);
	int select_min_task_num_queue(int task_1_num, int task_2_num, int task_3_num, int task_4_num);
	int select_min_task_num_queue_2(int task_1_num, int task_2_num);
	int select_min_task_num_queue_3(int task_1_num, int task_2_num, int task_3_num);
	int get_one_task_run_time(task* p, int* re_run_time);
	int divide_multi_core(multi_core m_c, core*** re_divide_core);
	int get_multi_core_order(multi_core m_c);
	int Insert_task(task** p, int* task_num, task* t);
	int DivQuadrants(task*** p_task, int* task_num);               //我感觉这里的建立四个任务子队列,根据象限建立的队列
	int DivQuadrants_2(task*** p_task, int* task_num);
	int DivQuadrants_3(task*** p_task, int* task_num);
	int get_height_core(multi_core m_c, int* no);
	int check_core_statu(core c);
	int trimTask(multi_core m_c, task** p, int* task_num, int task_qua, task*** p_h, int* task_num_h, int res_dif_v);
	int get_low_class_task(task** p, int* task_num, int* re_task_no);
	int task_sort_low(task** p, int* task_num);     //sortpriority
	int move_task(multi_core m_c, task* p_task, int from_qua, int to_qua, core** p_core);
	int migrateTask(task** p_task, int task_num, multi_core** re_m_c, multi_core m_c, int core_qua);
	int get_core_qua(int no, multi_core m_c);
	int get_qua_task_com_res(task** p, int task_num);
	int load_balance_to_eight_core(multi_core* m_c);
	int load_balance_to_two_core(multi_core* m_c);
	int Linux_load_balance_schedule();
	int DLBQ_load_balance_schedule(multi_core* m_c);
	int Base_load_balance_schedule(multi_core* m_c);
};