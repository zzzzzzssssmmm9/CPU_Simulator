#include "scheduler.h"


schedule::schedule()
{
	model = 0;
}

schedule::schedule(int m)
{
	model = m;
}

double schedule::get_banlance_class(double** p, int n, int m)
{
	math m_f;
	return m_f.S_D_double_sq_new_1(p, n, m);
}

int schedule::add_one_task_to_one_core(core c, task* t)
{
	if (c.add_one_task(*t))
	{
		return 1;
	}
	return 0;
}

int schedule::add_task_to_one_core(core c, task* p, int n)
{
	if (c.add_task(p, n))
	{
		return 1;
	}
	return 0;
}

int schedule::add_task_to_core(multi_core m_c, int start_core_no, task** p, int core_num, int* n)
{
	m_c.add_task(start_core_no, p, core_num, n);
	return 0;
}

int schedule::get_one_core_task(core c, int start_no, int num, task** q)
{
	if (c.get_task(start_no, num, q))
	{
		return 1;
	}
	return 0;
}

int schedule::get_core_task(multi_core m_c, int core_start_no, int core_num, task*** p, int* task_start_no, int* num)
{
	if (m_c.get_core_task(core_start_no, core_num, p, task_start_no, num))
	{
		return 0;
	}
	return 0;
}

int schedule::sort_prio(task** p,int task_num)
{
	int i, z;
	task* p_temp_task;
	for (i = 0; i < task_num - 1; i++)
	{
		for (z = 0; z < task_num - i - 1; z++)
		{
			if ((*(p[z])).get_prio() < (*(p[z + 1])).get_prio())
			{
				p_temp_task = p[z];
				p[z] = p[z + 1];
				p[z + 1] = p_temp_task;
			}
		}
	}
	return 0;
}

int schedule::get_cores()
{
	return 0;
}

int schedule::select_min_queue(task** p1, task** p2, task** p3, task** p4, int task_1_num, int task_2_num, int task_3_num, int task_4_num)
{
	math m;
	int res[4],min_queue;
	get_queue_run_time(p1, task_1_num, &res[0]);
	get_queue_run_time(p2, task_2_num, &res[1]);
	get_queue_run_time(p3, task_3_num, &res[2]);
	get_queue_run_time(p4, task_4_num, &res[3]);
	return m.int_min(res, 4);
}

int schedule::get_queue_run_time(task** p, int task_num, int* re_run_time)
{
	int i;
	int* temp_time;
	temp_time = new int;
	for (i = 0; i < task_num; i++)
	{
		get_one_task_run_time(p[i], temp_time);
		*re_run_time += *temp_time;
	}
	return 0;
}

int schedule::get_one_task_run_time(task* p, int* re_run_time)
{
	*re_run_time = p->get_time();
	return 0;
}

int schedule::divide_multi_core(multi_core m_c, core*** re_divide_core)
{
	int i, n = 0, x = 0, z = 0;
	math m;
	core** p_temp_core=m_c.get_p_core();
	int core_num = m_c.get_core_num();
	int core_num_order = m.get_2_order(core_num);
	int core_num_i = m.get_i_for_DLBQ(core_num_order);
	int core_num_j = m.get_j_for_DLBQ(core_num_order);
	int empty_core[1024];                          //这里把空位核心数写死了
	int empty_core_location[1024];
	m.get_q_for_DLBQ(core_num, empty_core);
	m.get_empty_core_location(empty_core, core_num_j, empty_core_location, core_num_i);
	if (core_num > 8)
	{
		for (i = 0; core_num / 2; i++)
		{
			if (i % core_num_i < core_num_i / 2)
			{
				if (i == empty_core_location[n])
				{
					n++;
				}
				else
				{
					re_divide_core[0][x] = p_temp_core[i];
					re_divide_core[2][x++] = p_temp_core[i + (core_num / 2)];

				}
			}
			else
			{
				if (i == empty_core_location[n])
				{
					n++;
				}
				else
				{
					re_divide_core[1][z] = p_temp_core[i];
					re_divide_core[3][z] = p_temp_core[i + (core_num / 2)];
				}
			}
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

int schedule::get_multi_core_order(multi_core m_c)
{
	math m;
	return m.get_2_order(m_c.get_core_num());
}

int schedule::Insert_task(task** p, task* t)
{

	return 0;
}