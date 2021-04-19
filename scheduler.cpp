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

int schedule::get_one_core_all_task(multi_core m_c, int core_no, task** q, int* re_task_num)
{
	m_c.get_one_core_all_task(core_no, q, re_task_num);
	return 0;
}

int schedule::get_core_all_task(multi_core m_c, int* core_no, int get_core_num, task*** q, int** task_num)
{
	m_c.get_core_all_task(core_no, get_core_num, q, task_num);
	return 0;
}

int schedule::get_task_queue(multi_core m_c, int* core_no, int get_core_num, task*** q, int** task_num)
{
	m_c.get_core_all_task(core_no, get_core_num, q, task_num);
	m_c.remove_core_all_task(core_no, get_core_num);
	return 0;
}

int schedule::get_all_core_all_task(multi_core m_c, int* re_core_num, task*** q, int** task_num)
{
	m_c.get_all_core_all_task(re_core_num, q, task_num);
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

int schedule::get_cores(multi_core m_c, multi_core** re_m_c)
{
	core*** p_temp_divide_core;
	int i, z, core_num;
	multi_core* p_temp_multi_core;
	core_num = m_c.get_core_num();
	p_temp_divide_core = new core ** [4];
	for (i = 0; i < 4; i++)
	{
		p_temp_divide_core[i] = new core * [1024];
	}
	divide_multi_core(m_c, p_temp_divide_core);
	for (i = 0; i < 4; i++)
	{
		p_temp_multi_core = new multi_core;
		p_temp_multi_core->set_core(core_num / 4, p_temp_divide_core[i]);
		re_m_c[i] = p_temp_multi_core;
	}
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

int schedule::Insert_task(task** p, int* task_num, task* t)
{
	p[(*task_num)++] = t;
	return 0;
}

int schedule::DivQuadrants(task*** p_task, int* task_num)
{
	int i;
	task** p_temp_task;
	p_task = new task * *[4];
	task_num = new int[4];
	for (i = 0; i < 4; i++)
	{
		p_temp_task = new task * [1024];
		p_task[i] = p_temp_task;
		task_num[i] = 0;
	}
	return 0;
}

int schedule::get_height_core(multi_core m_c, int* no)
{
	int i, z = 0;
	int core_num = m_c.get_core_num();
	core** p_core = m_c.get_p_core();
	for (i = 0; i < core_num; i++)
	{
		if (check_core_statu(*p_core[i]))
		{
			no[z++] = i;
		}
	}
	return 0;
}

int schedule::check_core_statu(core c)        //通过设置重载情况比例来设置重载情况
{
	if (c.check_state() >= 3)
	{
		return 1;
	}
	return 0;
}

int schedule::trimTask(task** p, int* task_num, task** p_h, int* task_num_h, int res_dif_v)
{
	int i;
	int* re_task_no;
	re_task_no = new int;
	sort_prio(p, *task_num);
	while (res_dif_v > 0)
	{
		res_dif_v -= p[--(*task_num)]->get_com();
		p_h[(*task_num_h)++] = p[(*task_num)];
		p[(*task_num)] = NULL;
	}
	return 0;
}

int schedule::get_low_class_task(task** p, int* task_num, int* re_task_no)
{
	int i, min_prio, min_prio_loc, temp_min_prio;
	min_prio = (*p[0]).get_prio();
	min_prio_loc = 0;
	for (i = 0; i < *task_num; i++)
	{
		temp_min_prio = (*p[i]).get_prio();
		if (temp_min_prio < min_prio)
		{
			min_prio = temp_min_prio;
			min_prio_loc = i;
		}
	}
	*re_task_no = min_prio_loc;
	return 0;
}

int schedule::migrateTask(task*** p_task, int* task_num, multi_core** re_m_c)
{
	int i;
	
	return 0;
}