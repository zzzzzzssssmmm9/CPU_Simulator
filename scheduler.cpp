#include "scheduler.h"


schedule::schedule()
{
	model = 0;
}

schedule::schedule(int m)
{
	model = m;
}

int schedule::set_modle(int m)
{
	model = m;
	return 0;
}

double schedule::get_banlance_class(double** p, int n, int m)
{
	math m_f;
	return m_f.S_D_double_sq_new_1(p, n, m);
}

int schedule::add_one_task_to_one_core(core c, task* t)
{
	if (c.add_one_task(*t, 0))
	{
		return 1;
	}
	return 0;
}

int schedule::add_task_to_one_core(core c, task* p, int n)
{
	if (c.add_task(p, n, 0))
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

int schedule::sort_prio(task** p,int task_num)       //优先级按照降序排列
{
	int i, z;
	task* p_temp_task;
	for (i = 0; i < task_num - 1; i++)
	{
		for (z = 0; z < task_num - i - 1; z++)
		{
			if ((p[z])->get_prio() < (p[z + 1])->get_prio())
			{
				p_temp_task = p[z];
				p[z] = p[z + 1];
				p[z + 1] = p_temp_task;
			}
		}
	}
	return 0;
}

int schedule::get_task_pp(task*** q, int** task_num, int core_num, task** p, int* task_n)
{
	int i,z;
	*task_n = 0;
	for (i = 0; i < core_num; i++)
	{
		for (z = 0; z < *(task_num[i]); z++)
		{
			p[(*task_n)++] = q[i][z];
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

int schedule::select_min_queue_2(task** p1, task** p2, int task_1_num, int task_2_num)
{
	math m;
	int res[2], min_queue;
	get_queue_run_time(p1, task_1_num, &res[0]);
	get_queue_run_time(p2, task_2_num, &res[1]);
	return m.int_min(res, 2);
}

int schedule::select_min_queue_3(task** p1, task** p2, task** p3, int task_1_num, int task_2_num, int task_3_num)
{
	math m;
	int res[4], min_queue;
	get_queue_run_time(p1, task_1_num, &res[0]);
	get_queue_run_time(p2, task_2_num, &res[1]);
	get_queue_run_time(p3, task_3_num, &res[2]);
	return m.int_min(res, 3);
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

int schedule::select_min_task_num_queue(int task_1_num, int task_2_num, int task_3_num, int task_4_num)
{
	math m;
	int res[4] = { task_1_num,task_2_num,task_3_num,task_4_num };
	return m.int_min(res, 4);
}

int schedule::select_min_task_num_queue_2(int task_1_num, int task_2_num)
{
	math m;
	int res[2] = { task_1_num,task_2_num };
	return m.int_min(res, 2);
}

int schedule::select_min_task_num_queue_3(int task_1_num, int task_2_num, int task_3_num)
{
	math m;
	int res[3] = { task_1_num,task_2_num,task_3_num };
	return m.int_min(res, 3);
}

int schedule::get_one_task_run_time(task* p, int* re_run_time)
{
	*re_run_time = p->get_time();
	return 0;
}

int schedule::divide_multi_core(multi_core m_c, core*** re_divide_core)
{
	int i, n = 0, x = 0, z = 0, temp_core_no = 0, temp_empty_core_no = 0;
	math m;
	core** p_temp_core=m_c.get_p_core();
	int core_num = m_c.get_core_num();
	int core_num_order = m.get_2_order(core_num);
	int core_num_i = m.get_i_for_DLBQ(core_num_order);
	int core_num_j;
	if (core_num_order % 2 != 0)
	{
		core_num_j = m.get_j_for_DLBQ(core_num_order);
		int empty_core[1024];                          //这里把空位核心数写死了
		int empty_core_location[1024];
		m.get_q_for_DLBQ(core_num_order, empty_core);
		m.get_empty_core_location(empty_core, core_num_j, empty_core_location, core_num_i);
		if (core_num > 8)
		{
			for (i = 0; i < ((core_num_i * core_num_i) / 2); i++)
			{
				if (i % core_num_i < core_num_i / 2)
				{
					if (i == empty_core_location[temp_empty_core_no])
					{
						temp_empty_core_no++;
					}
					else 
					{
						re_divide_core[1][x] = p_temp_core[temp_core_no];
						re_divide_core[2][x++] = p_temp_core[temp_core_no + (core_num / 2)];
						temp_core_no++;
					}
				}
				else
				{
					if (i == empty_core_location[temp_empty_core_no])
					{
						temp_empty_core_no++;
					}
					else
					{
						re_divide_core[0][z] = p_temp_core[temp_core_no];
						re_divide_core[3][z++] = p_temp_core[temp_core_no + (core_num / 2)];
						temp_core_no++;
					}
				}
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (core_num > 2)
		{
			for (i = 0; i < (core_num / 2); i++)
			{
				if (i % core_num_i < core_num_i / 2)
				{
					
					re_divide_core[1][x] = p_temp_core[i];
					re_divide_core[2][x++] = p_temp_core[i + (core_num / 2)];
				}
				else
				{
					re_divide_core[0][z] = p_temp_core[i];
					re_divide_core[3][z++] = p_temp_core[i + (core_num / 2)];
				}
			}
		}
		else
		{
			return 1;
		}
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

int schedule::DivQuadrants_2(task*** p_task, int* task_num)
{
	int i;
	task** p_temp_task;
	p_task = new task * *[2];
	task_num = new int[2];
	for (i = 0; i < 2; i++)
	{
		p_temp_task = new task * [1024];
		p_task[i] = p_temp_task;
		task_num[i] = 0;
	}
	return 0;
}

int schedule::DivQuadrants_3(task*** p_task, int* task_num)
{
	int i;
	task** p_temp_task;
	p_task = new task * *[3];
	task_num = new int[3];
	for (i = 0; i < 3; i++)
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
	c.check_state();
	if (c.get_state() >= 3)
	{
		return 1;
	}
	return 0;
}

int schedule::trimTask(multi_core m_c, task** p, int* task_num, int task_qua, task*** p_h, int* task_num_h, int res_dif_v)     //该函数需要给出待检测队列
{
	int i,z;
	int temp_core_no;
	int temp_qua;
	sort_prio(p, *task_num);          
	while (res_dif_v > 0)
	{
		i = 1;
		temp_core_no = p[(*task_num) - i]->get_core_no();
		temp_qua = get_core_qua(temp_core_no, m_c);
		if (temp_qua != task_qua)
		{
			res_dif_v -= p[--(*task_num)]->get_com();
			p_h[temp_qua][(task_num_h[temp_qua])++] = p[(*task_num)];
			p[(*task_num)] = NULL;
		}
		else
		{
			while (temp_qua == task_qua)
			{
				temp_core_no = p[(*task_num) - i]->get_core_no();
				temp_qua = get_core_qua(temp_core_no, m_c);
				i++;
			}
			res_dif_v -= p[(*task_num) - i]->get_com();
			p_h[temp_qua][(task_num_h[temp_qua])++] = p[(*task_num) - i];
			for (z = 0; z < i - 1; z++)
			{
				p[(*task_num) - i + z] = p[(*task_num) - i + z + 1];
			}
			p[--(*task_num)] = NULL;
		}
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

int schedule::migrateTask(task** p_task, int task_num, multi_core** re_m_c, multi_core m_c, int core_qua)
{
	int i;
	int task_qua, task_core_no;
	int move_dis = 0;
	int move_num = 0;
	int multi_core_have_core_num;
	multi_core_have_core_num = m_c.get_core_num();
	if (multi_core_have_core_num != 8 && multi_core_have_core_num != 1 && multi_core_have_core_num != 2)
	{
		for (i = 0; i < task_num; i++)
		{
			task_core_no = (*(p_task[i])).get_core_no();
			task_qua = get_core_qua(task_core_no, m_c);
			move_task(m_c, p_task[i], task_qua, core_qua, (re_m_c[core_qua])->get_p_core(), &move_dis, &move_num);
		}
	}
	printf("move num: %d move dis: %d\n", move_num, move_dis);
	return 0;
}

int schedule::migrateTask_B(task** p_task, int task_num, multi_core** re_m_c, multi_core m_c, int core_qua)
{
	int i;
	int task_qua, task_core_no;
	int move_dis = 0;
	int move_num = 0;
	int multi_core_have_core_num;
	multi_core_have_core_num = m_c.get_core_num();
	if (multi_core_have_core_num != 8 && multi_core_have_core_num != 1 && multi_core_have_core_num != 2)
	{
		for (i = 0; i < task_num; i++)
		{
			task_core_no = (*(p_task[i])).get_core_no();
			task_qua = get_core_qua(task_core_no, m_c);
			move_task_B(m_c, p_task[i], task_qua, core_qua, (re_m_c[core_qua])->get_p_core(), &move_dis, &move_num);
		}
	}
	printf("move num: %d move dis: %d\n", move_num, move_dis);
	return 0;
}

int schedule::get_core_qua(int no, multi_core m_c)
{
	math m;
	int core_num = m_c.get_core_num();
	int core_order = m.get_2_order(core_num);
	int i = m.get_i_for_DLBQ(core_order);
	int j = m.get_j_for_DLBQ(core_order);
	int temp_no;
	if (core_order % 2 == 0)
	{
		if (no >= (core_num / 2))
		{
			no -= (core_num / 2);
			while (no >= i)
			{
				no -= i;
			}
			if (no < (i / 2))
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
		else
		{
			while (no >= i)
			{
				no -= i;
			}
			if (no < (i / 2))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if (core_num == 2)
		{
			if (no)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		if (no >= (core_num / 2))
		{
			no -= (core_num / 2);
			temp_no = no % (j * 8 * (j / 2));
			if (temp_no < i)
			{
				if (temp_no < (i / 2))
				{
					return 2;
				}
				else
				{
					return 3;
				}
			}
			else if (temp_no < i * 2 - j)
			{
				if (temp_no < (i + (i / 2) - (j / 2)))
				{
					return 2;
				}
				else
				{
					return 3;
				}
			}
			else
			{
				if (temp_no < (i * 2 - j + i / 2))
				{
					return 2;
				}
				else
				{
					return 3;
				}
			}
		}
		else
		{
			temp_no = no % (j * 8 * (j / 2));
			if (temp_no < i)
			{
				if (temp_no < (i / 2))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else if (temp_no < i * 2 - j)
			{
				if (temp_no < (i + (i / 2) - (j / 2)))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (temp_no < (i * 2 - j + i / 2))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
	return -1;
}

int schedule::move_task(multi_core m_c, task* p_task, int from_qua, int to_qua, core** p_core, int* move_dis, int* move_num)
{
	math m;
	int z, line, colum, no = 0;
	int temp_line = 0, temp_colum = 0;
	int core_no = p_task->get_core_no();
	int core_num = m_c.get_core_num();
	int core_order = m.get_2_order(core_num);
	int i = m.get_i_for_DLBQ(core_order);
	int j = m.get_j_for_DLBQ(core_order);
	(*move_num)++;
	if (core_order % 2 == 0)
	{
		line = m.get_line_on_even_k(core_no, i, j);
		colum = m.get_column_on_even_k(core_no, i, j);
		if (from_qua == 0)
		{
			if (to_qua == 0)
			{
				no = line * (i / 2);
				no = no + colum - (i / 2);
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 1)
			{
				no = (line + 1) * (i / 2);
				no -= 1;
				(*move_dis) += (colum - (i / 2) + 1);
			}
			else if (to_qua == 2)
			{
				no = i / 2 - 1;
				(*move_dis) += (colum - (i / 2) + 1 + (i / 2) - line);
			}
			else if (to_qua == 3)
			{
				no = colum - (i / 2);
				(*move_dis) += ((i / 2) - line);
			}
		}
		else if (from_qua == 1)
		{
			if (to_qua == 0)
			{
				no = line * (i / 2);
				(*move_dis) += ((i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				no = line * (i / 2);
				no = no + colum;
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 2)
			{
				no = colum;
				(*move_dis) += ((i / 2) - line);
			}
			else if (to_qua == 3)
			{
				no = 0;
				(*move_dis) += (2 * (i / 2) - line - colum);
			}
		}
		else if (from_qua == 2)
		{
			if (to_qua == 0)
			{
				no = (i / 2) * ((i / 2) - 1);
				(*move_dis) += (line - (i / 2) + 1 + (i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				no = (i / 2) * ((i / 2) - 1);
				no += colum;
				(*move_dis) += (line - (i / 2) + 1);
			}
			else if (to_qua == 2)
			{
				no = (line - (i / 2)) * (i / 2);
				no += colum;
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 3)
			{
				no = (line - (i / 2)) * (i / 2);
				(*move_dis) += ((i / 2) - colum);
			}
		}
		else if (from_qua == 3)
		{
			if (to_qua == 0)
			{
				no = (i / 2) * ((i / 2) - 1);
				no = no + colum - (i / 2);
				(*move_dis) += (line - (i / 2) + 1);
			}
			else if (to_qua == 1)
			{
				no = (i / 2) * (i / 2) - 1;
				(*move_dis) += (line - (i / 2) + 1 + colum - (i / 2) + 1);
			}
			else if (to_qua == 2)
			{
				no = (1 + (line - (i / 2))) * (i / 2);
				no -= 1;
				(*move_dis) += (colum - (i / 2) + 1);
			}
			else if (to_qua == 3)
			{
				no = (line - (i / 2)) * (i / 2);
				no = no + colum - (i / 2);
				(*move_dis) += 0;
				(*move_num)--;
			}
		}
	}
	else
	{
		line = m.get_line_on_odd_k(core_no, i, j);
		colum = m.get_column_on_odd_k(core_no, i, j);
		if (from_qua == 0)
		{
			if (to_qua == 0)
			{
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{
					no = no + colum - (i / 2);
				}
				else if (line == 1)
				{
					no += (i / 2);
					colum -= (i / 2);
					while (colum > 2)
					{
						colum -= 3;
						no += 2;
					}
					if (colum == 2)
					{
						no++;
					}
				}
				else
				{
					no = no + 2 * (i / 2) - (j / 2);
					no = no + colum - (i / 2);
				}
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 1)
			{
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{
					no = no + (i / 2) - 1;
				}
				else if (line == 1)
				{
					no = no + (i / 2) - 1;
					no = no + (j / 2) * 2 - 1;
				}
				else
				{
					no = no + (j / 2) * 8 - 1;
				}
				(*move_dis) += (colum - (i / 2) + 1);
			}
			else if (to_qua == 2)
			{
				no = (i / 2) - 1;
				(*move_dis) += (colum - (i / 2) + 1 + (i / 2) - line);
			}
			else if (to_qua == 3)
			{
				no = colum - (i / 2);
				(*move_dis) += ((i / 2) - line);
			}
		}
		else if (from_qua == 1)
		{
			if (to_qua == 0)
			{
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{

				}
				else if (line == 1)
				{
					no = no + (i / 2);
				}
				else
				{
					no = no + (i / 2);
					no = no + (j / 2) * 2;
				}
				(*move_dis) += ((i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{
					no += colum;
				}
				else if (line == 1)
				{
					no += (i / 2);
					while (colum > 2)
					{
						no += 2;
						colum -= 3;
					}
					if (colum == 2)
					{
						no++;
					}
				}
				else
				{
					no = no + (i / 2) * 2 - (j / 2);
					no += colum;
				}
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 2)
			{
				no = colum;
				(*move_dis) += ((i / 2) - line);
			}
			else if (to_qua == 3)
			{
				no = 0;
				(*move_dis) += (2 * (i / 2) - line - colum);
			}
		}
		else if (from_qua == 2)
		{
			if (to_qua == 0)
			{
				no = (j / 2) * (j / 2) * 8;
				no -= (i / 2);
				(*move_dis) += (line - (i / 2) + 1 + (i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				no = (j / 2) * (j / 2) * 8;
				no -= (i / 2);
				no += colum;
				(*move_dis) += (line - (i / 2) + 1);
			}
			else if (to_qua == 2)
			{
				line -= (i / 2);
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{
					no += colum;
				}
				else if (line == 1)
				{
					no = no + (i / 2);
					while (colum > 2)
					{
						no += 2;
						colum -= 3;
					}
					if (colum == 2)
					{
						no++;
					}
				}
				else
				{
					no = no + (i / 2) * 2 - (j / 2);
					no += colum;
				}
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 3)
			{
				line -= (i / 2);
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{
					
				}
				else if (line == 1)
				{
					no = no + (i / 2);
				}
				else
				{
					no = no + (i / 2);
					no = no + (j / 2) * 2;
				}
				(*move_dis) += ((i / 2) - colum);
			}
		}
		else if (from_qua == 3)
		{
			if (to_qua == 0)
			{
				no = (j / 2) * (j / 2) * 8;
				no -= (i / 2);
				no = no + colum - (i / 2);
				(*move_dis) += (line - (i / 2) + 1);
			}
			else if (to_qua == 1)
			{
				no = (j / 2) * (j / 2) * 8;
				no--;
				(*move_dis) += (line - (i / 2) + 1 + colum - (i / 2) + 1);
			}
			else if (to_qua == 2)
			{
				line -= (i / 2);
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{
					no = no + (i / 2) - 1;
				}
				else if (line == 1)
				{
					no = no + (i / 2) * 2 - (j / 2) - 1;
				}
				else
				{
					no += (j / 2) * 8 - 1;
				}
				(*move_dis) += (colum - (i / 2) + 1);
			}
			else if (to_qua == 3)
			{
				line -= (i / 2);
				while (line > 2)
				{
					temp_line++;
					line -= 3;
				}
				no += temp_line * (j / 2) * 8;
				if (line == 0)
				{
					no = no + colum - (i / 2);
				}
				else if (line == 1)
				{
					no += (i / 2);
					colum -= (i / 2);
					while (colum > 2)
					{
						no += 2;
						colum -= 3;
					}
					if (colum == 2)
					{
						no++;
					}
				}
				else
				{
					no = no + (i / 2) * 2 - (j / 2);
					no = no + colum - (i / 2);
				}
				(*move_dis) += 0;
				(*move_num)--;
			}
		}
	}
	p_core[no]->add_one_task(*p_task, no);
	return 0;
}

int schedule::move_task_B(multi_core m_c, task* p_task, int from_qua, int to_qua, core** p_core, int* move_dis, int* move_num)
{
	math m;
	int z, line, colum;
	int temp_line = 0, temp_colum = 0;
	int core_no = p_task->get_core_no();
	int core_num = m_c.get_core_num();
	int core_order = m.get_2_order(core_num);
	int i = m.get_i_for_DLBQ(core_order);
	int j = m.get_j_for_DLBQ(core_order);
	(*move_num)++;
	if (core_order % 2 == 0)
	{
		line = m.get_line_on_even_k(core_no, i, j);
		colum = m.get_column_on_even_k(core_no, i, j);
		if (from_qua == 0)
		{
			if (to_qua == 0)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 1)
			{
				(*move_dis) += (line + colum);
			}
			else if (to_qua == 2)
			{
				(*move_dis) += (colum + (i / 2) - line);
			}
			else if (to_qua == 3)
			{
				(*move_dis) += (colum - (i / 2) + (i / 2) - line);
			}
		}
		else if (from_qua == 1)
		{
			if (to_qua == 0)
			{
				(*move_dis) += (line + (i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 2)
			{
				(*move_dis) += (colum + (i / 2) - line);
			}
			else if (to_qua == 3)
			{
				(*move_dis) += ((i / 2) - line + (i / 2) - colum);
			}
		}
		else if (from_qua == 2)
		{
			if (to_qua == 0)
			{
				(*move_dis) += (line + (i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				(*move_dis) += (line + colum);
			}
			else if (to_qua == 2)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 3)
			{
				(*move_dis) += (line - (i / 2) + (i / 2) - colum);
			}
		}
		else if (from_qua == 3)
		{
			if (to_qua == 0)
			{
				(*move_dis) += (line + colum - (i / 2));
			}
			else if (to_qua == 1)
			{
				(*move_dis) += (line + colum);
			}
			else if (to_qua == 2)
			{
				(*move_dis) += (line - (i / 2) + colum);
			}
			else if (to_qua == 3)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
		}
	}
	else
	{
		line = m.get_line_on_odd_k(core_no, i, j);
		colum = m.get_column_on_odd_k(core_no, i, j);
		if (from_qua == 0)
		{
			if (to_qua == 0)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 1)
			{
				(*move_dis) += (line + colum);
			}
			else if (to_qua == 2)
			{
				(*move_dis) += (colum + (i / 2) - line);
			}
			else if (to_qua == 3)
			{
				(*move_dis) += (colum - (i / 2) + (i / 2) - line);
			}
		}
		else if (from_qua == 1)
		{
			if (to_qua == 0)
			{
				(*move_dis) += (line + (i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 2)
			{
				(*move_dis) += (colum + (i / 2) - line);
			}
			else if (to_qua == 3)
			{
				(*move_dis) += ((i / 2) - line + (i / 2) - colum);
			}
		}
		else if (from_qua == 2)
		{
			if (to_qua == 0)
			{
				(*move_dis) += (line + (i / 2) - colum);
			}
			else if (to_qua == 1)
			{
				(*move_dis) += (line + colum);
			}
			else if (to_qua == 2)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
			else if (to_qua == 3)
			{
				(*move_dis) += (line - (i / 2) + (i / 2) - colum);
			}
		}
		else if (from_qua == 3)
		{
			if (to_qua == 0)
			{
				(*move_dis) += (line + colum - (i / 2));
			}
			else if (to_qua == 1)
			{
				(*move_dis) += (line + colum);
			}
			else if (to_qua == 2)
			{
				(*move_dis) += (line - (i / 2) + colum);
			}
			else if (to_qua == 3)
			{
				(*move_dis) += 0;
				(*move_num)--;
			}
		}
	}
	p_core[0]->add_one_task(*p_task, 0);
	return 0;
}

int schedule::get_qua_task_com_res(task** p, int task_num)
{
	int i, com_res = 0;
	for (i = 0; i < task_num; i++)
	{
		com_res += (p[i])->get_com();
	}
	return com_res;
}

int schedule::load_balance_to_eight_core(multi_core* m_c)      //在面对有八个处理器核心时，无论重载核出现在哪个位置，将这种多核处理器任务迁移最多迁移4次，每次都将任务向紧接着的核心迁移，直到迁移到最后一个核心或不出现重载核，可能出现最后一个核心重载而其他核心满载的状态
{
	int i, z;
	core** pp_temp_core;
	task** pp_temp_task;
	int core_res_re;
	int temp_task_com;
	int temp_task_prio;
	int height_core_no = 0;
	int have_height_core = -1;
	pp_temp_task = new task * [1024];
	pp_temp_core = (*m_c).get_p_core();
	for (i = 0; i < 8; i++)
	{
		if (check_core_statu(*(pp_temp_core[i])))
		{
			height_core_no = i;
			have_height_core++;
		}
	}
	if (have_height_core)
	{
		if (height_core_no == 0)
		{
			i = 0;
			core_res_re = pp_temp_core[0]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[0]->get_first_task_prio();
				temp_task_com = pp_temp_core[0]->get_first_task_com();
				pp_temp_core[0]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[0]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
				}
				else
				{
					pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
				}
			}
			if (pp_temp_core[1]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[1]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[1]->get_first_task_prio();
					temp_task_com = pp_temp_core[1]->get_first_task_com();
					pp_temp_core[1]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[1]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
				}
				if (pp_temp_core[2]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[2]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[2]->get_first_task_prio();
						temp_task_com = pp_temp_core[2]->get_first_task_com();
						pp_temp_core[2]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[2]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
					}
					if (pp_temp_core[4]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[4]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[4]->get_first_task_prio();
							temp_task_com = pp_temp_core[4]->get_first_task_com();
							pp_temp_core[4]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[4]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
						}
					}

				}
			}
			if (pp_temp_core[3]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[3]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[3]->get_first_task_prio();
					temp_task_com = pp_temp_core[3]->get_first_task_com();
					pp_temp_core[3]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[3]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
				}
				if (pp_temp_core[5]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[5]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[5]->get_first_task_prio();
						temp_task_com = pp_temp_core[5]->get_first_task_com();
						pp_temp_core[5]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[5]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
					}
					if (pp_temp_core[6]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[6]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[6]->get_first_task_prio();
							temp_task_com = pp_temp_core[6]->get_first_task_com();
							pp_temp_core[6]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[6]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
						}
					}
				}
			}
		}
		else if (height_core_no == 1)
		{
			i = 0;
			core_res_re = pp_temp_core[1]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[1]->get_first_task_prio();
				temp_task_com = pp_temp_core[1]->get_first_task_com();
				pp_temp_core[1]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[1]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
				}
				else
				{
					pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
				}
			}
			if (pp_temp_core[0]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[0]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[0]->get_first_task_prio();
					temp_task_com = pp_temp_core[0]->get_first_task_com();
					pp_temp_core[0]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[0]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
				}
				if (pp_temp_core[3]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[3]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[3]->get_first_task_prio();
						temp_task_com = pp_temp_core[3]->get_first_task_com();
						pp_temp_core[3]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[3]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
					}
					if (pp_temp_core[5]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[5]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[5]->get_first_task_prio();
							temp_task_com = pp_temp_core[5]->get_first_task_com();
							pp_temp_core[5]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[5]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
						}
					}

				}
			}
			if (pp_temp_core[2]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[2]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[2]->get_first_task_prio();
					temp_task_com = pp_temp_core[2]->get_first_task_com();
					pp_temp_core[2]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[2]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
				}
				if (pp_temp_core[4]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[4]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[4]->get_first_task_prio();
						temp_task_com = pp_temp_core[4]->get_first_task_com();
						pp_temp_core[4]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[4]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
					}
					if (pp_temp_core[7]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[7]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[7]->get_first_task_prio();
							temp_task_com = pp_temp_core[7]->get_first_task_com();
							pp_temp_core[7]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[7]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
						}
					}
				}
			}
		}
		else if (height_core_no == 2)
		{
			i = 0;
			core_res_re = pp_temp_core[2]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[2]->get_first_task_prio();
				temp_task_com = pp_temp_core[2]->get_first_task_com();
				pp_temp_core[2]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[2]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
				}
				else
				{
					pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
				}
			}
			if (pp_temp_core[1]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[1]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[1]->get_first_task_prio();
					temp_task_com = pp_temp_core[1]->get_first_task_com();
					pp_temp_core[1]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[1]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
				}
				if (pp_temp_core[0]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[0]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[0]->get_first_task_prio();
						temp_task_com = pp_temp_core[0]->get_first_task_com();
						pp_temp_core[0]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[0]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
					}
					if (pp_temp_core[3]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[3]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[3]->get_first_task_prio();
							temp_task_com = pp_temp_core[3]->get_first_task_com();
							pp_temp_core[3]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[3]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
						}
					}

				}
			}
			if (pp_temp_core[4]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[4]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[4]->get_first_task_prio();
					temp_task_com = pp_temp_core[4]->get_first_task_com();
					pp_temp_core[4]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[4]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
				}
				if (pp_temp_core[7]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[7]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[7]->get_first_task_prio();
						temp_task_com = pp_temp_core[7]->get_first_task_com();
						pp_temp_core[7]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[7]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
					}
					if (pp_temp_core[6]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[6]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[6]->get_first_task_prio();
							temp_task_com = pp_temp_core[6]->get_first_task_com();
							pp_temp_core[6]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[6]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
						}
					}
				}
			}
		}
		else if (height_core_no == 3)
		{
			i = 0;
			core_res_re = pp_temp_core[3]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[3]->get_first_task_prio();
				temp_task_com = pp_temp_core[3]->get_first_task_com();
				pp_temp_core[3]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[3]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
				}
				else
				{
					pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
				}
			}
			if (pp_temp_core[0]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[0]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[0]->get_first_task_prio();
					temp_task_com = pp_temp_core[0]->get_first_task_com();
					pp_temp_core[0]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[0]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
				}
				if (pp_temp_core[1]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[1]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[1]->get_first_task_prio();
						temp_task_com = pp_temp_core[1]->get_first_task_com();
						pp_temp_core[1]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[1]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
					}
					if (pp_temp_core[2]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[2]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[2]->get_first_task_prio();
							temp_task_com = pp_temp_core[2]->get_first_task_com();
							pp_temp_core[2]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[2]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
						}
					}

				}
			}
			if (pp_temp_core[5]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[5]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[5]->get_first_task_prio();
					temp_task_com = pp_temp_core[5]->get_first_task_com();
					pp_temp_core[5]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[5]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
				}
				if (pp_temp_core[6]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[6]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[6]->get_first_task_prio();
						temp_task_com = pp_temp_core[6]->get_first_task_com();
						pp_temp_core[6]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[6]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
					}
					if (pp_temp_core[7]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[7]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[7]->get_first_task_prio();
							temp_task_com = pp_temp_core[7]->get_first_task_com();
							pp_temp_core[7]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[7]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
						}
					}
				}
			}
		}
		else if (height_core_no == 4)
		{
			i = 0;
			core_res_re = pp_temp_core[4]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[4]->get_first_task_prio();
				temp_task_com = pp_temp_core[4]->get_first_task_com();
				pp_temp_core[4]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[4]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
				}
				else
				{
					pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
				}
			}
			if (pp_temp_core[2]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[2]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[2]->get_first_task_prio();
					temp_task_com = pp_temp_core[2]->get_first_task_com();
					pp_temp_core[2]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[2]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
				}
				if (pp_temp_core[1]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[1]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[1]->get_first_task_prio();
						temp_task_com = pp_temp_core[1]->get_first_task_com();
						pp_temp_core[1]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[1]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
					}
					if (pp_temp_core[0]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[0]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[0]->get_first_task_prio();
							temp_task_com = pp_temp_core[0]->get_first_task_com();
							pp_temp_core[0]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[0]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
						}
					}

				}
			}
			if (pp_temp_core[7]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[7]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[7]->get_first_task_prio();
					temp_task_com = pp_temp_core[7]->get_first_task_com();
					pp_temp_core[7]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[7]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
				}
				if (pp_temp_core[6]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[6]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[6]->get_first_task_prio();
						temp_task_com = pp_temp_core[6]->get_first_task_com();
						pp_temp_core[6]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[6]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
					}
					if (pp_temp_core[5]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[5]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[5]->get_first_task_prio();
							temp_task_com = pp_temp_core[5]->get_first_task_com();
							pp_temp_core[5]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[5]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
						}
					}
				}
			}
		}
		else if (height_core_no == 5)
		{
			i = 0;
			core_res_re = pp_temp_core[5]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[5]->get_first_task_prio();
				temp_task_com = pp_temp_core[5]->get_first_task_com();
				pp_temp_core[5]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[5]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
				}
				else
				{
					pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
				}
			}
			if (pp_temp_core[3]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[3]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[3]->get_first_task_prio();
					temp_task_com = pp_temp_core[3]->get_first_task_com();
					pp_temp_core[3]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[3]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
				}
				if (pp_temp_core[0]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[0]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[0]->get_first_task_prio();
						temp_task_com = pp_temp_core[0]->get_first_task_com();
						pp_temp_core[0]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[0]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
					}
					if (pp_temp_core[1]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[1]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[1]->get_first_task_prio();
							temp_task_com = pp_temp_core[1]->get_first_task_com();
							pp_temp_core[1]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[1]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
						}
					}

				}
			}
			if (pp_temp_core[6]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[6]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[6]->get_first_task_prio();
					temp_task_com = pp_temp_core[6]->get_first_task_com();
					pp_temp_core[6]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[6]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
				}
				if (pp_temp_core[7]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[7]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[7]->get_first_task_prio();
						temp_task_com = pp_temp_core[7]->get_first_task_com();
						pp_temp_core[7]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[7]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
					}
					if (pp_temp_core[4]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[4]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[4]->get_first_task_prio();
							temp_task_com = pp_temp_core[4]->get_first_task_com();
							pp_temp_core[4]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[4]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
						}
					}
				}
			}
		}
		else if (height_core_no == 6)
		{
			i = 0;
			core_res_re = pp_temp_core[6]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[6]->get_first_task_prio();
				temp_task_com = pp_temp_core[6]->get_first_task_com();
				pp_temp_core[6]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[6]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
				}
				else
				{
					pp_temp_core[7]->add_one_task(*(pp_temp_task[z]), 7);
				}
			}
			if (pp_temp_core[5]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[5]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[5]->get_first_task_prio();
					temp_task_com = pp_temp_core[5]->get_first_task_com();
					pp_temp_core[5]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[5]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
				}
				if (pp_temp_core[3]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[3]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[3]->get_first_task_prio();
						temp_task_com = pp_temp_core[3]->get_first_task_com();
						pp_temp_core[3]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[3]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
					}
					if (pp_temp_core[0]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[0]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[0]->get_first_task_prio();
							temp_task_com = pp_temp_core[0]->get_first_task_com();
							pp_temp_core[0]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[0]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
						}
					}

				}
			}
			if (pp_temp_core[7]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[7]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[7]->get_first_task_prio();
					temp_task_com = pp_temp_core[7]->get_first_task_com();
					pp_temp_core[7]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[7]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
				}
				if (pp_temp_core[4]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[4]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[4]->get_first_task_prio();
						temp_task_com = pp_temp_core[4]->get_first_task_com();
						pp_temp_core[4]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[4]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
					}
					if (pp_temp_core[2]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[2]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[2]->get_first_task_prio();
							temp_task_com = pp_temp_core[2]->get_first_task_com();
							pp_temp_core[2]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[2]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
						}
					}
				}
			}
		}
		else
		{
			i = 0;
			core_res_re = pp_temp_core[7]->get_com_res_re();
			while (core_res_re < 0)
			{
				temp_task_prio = pp_temp_core[7]->get_first_task_prio();
				temp_task_com = pp_temp_core[7]->get_first_task_com();
				pp_temp_core[7]->get_one_task(1, pp_temp_task[i++]);
				pp_temp_core[7]->remove_one_task(0);
				if (temp_task_prio)
				{
					core_res_re += temp_task_com;
				}
				else
				{
					i--;
				}
			}
			for (z = 0; z < i; z++)
			{
				if ((z % 2) == 0)
				{
					pp_temp_core[4]->add_one_task(*(pp_temp_task[z]), 4);
				}
				else
				{
					pp_temp_core[6]->add_one_task(*(pp_temp_task[z]), 6);
				}
			}
			if (pp_temp_core[4]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[4]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[4]->get_first_task_prio();
					temp_task_com = pp_temp_core[4]->get_first_task_com();
					pp_temp_core[4]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[4]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[2]->add_one_task(*(pp_temp_task[z]), 2);
				}
				if (pp_temp_core[2]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[2]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[2]->get_first_task_prio();
						temp_task_com = pp_temp_core[2]->get_first_task_com();
						pp_temp_core[2]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[2]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[1]->add_one_task(*(pp_temp_task[z]), 1);
					}
					if (pp_temp_core[1]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[1]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[1]->get_first_task_prio();
							temp_task_com = pp_temp_core[1]->get_first_task_com();
							pp_temp_core[1]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[1]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
						}
					}

				}
			}
			if (pp_temp_core[6]->check_state() >= 3)
			{
				i = 0;
				core_res_re = pp_temp_core[6]->get_com_res_re();
				while (core_res_re < 0)
				{
					temp_task_prio = pp_temp_core[6]->get_first_task_prio();
					temp_task_com = pp_temp_core[6]->get_first_task_com();
					pp_temp_core[6]->get_one_task(1, pp_temp_task[i++]);
					pp_temp_core[6]->remove_one_task(0);
					if (temp_task_prio)
					{
						core_res_re += temp_task_com;
					}
					else
					{
						i--;
					}
				}
				for (z = 0; z < i; z++)
				{
					pp_temp_core[5]->add_one_task(*(pp_temp_task[z]), 5);
				}
				if (pp_temp_core[5]->check_state() >= 3)
				{
					i = 0;
					core_res_re = pp_temp_core[5]->get_com_res_re();
					while (core_res_re < 0)
					{
						temp_task_prio = pp_temp_core[5]->get_first_task_prio();
						temp_task_com = pp_temp_core[5]->get_first_task_com();
						pp_temp_core[5]->get_one_task(1, pp_temp_task[i++]);
						pp_temp_core[5]->remove_one_task(0);
						if (temp_task_prio)
						{
							core_res_re += temp_task_com;
						}
						else
						{
							i--;
						}
					}
					for (z = 0; z < i; z++)
					{
						pp_temp_core[3]->add_one_task(*(pp_temp_task[z]), 3);
					}
					if (pp_temp_core[3]->check_state() >= 3)
					{
						i = 0;
						core_res_re = pp_temp_core[3]->get_com_res_re();
						while (core_res_re < 0)
						{
							temp_task_prio = pp_temp_core[3]->get_first_task_prio();
							temp_task_com = pp_temp_core[3]->get_first_task_com();
							pp_temp_core[3]->get_one_task(1, pp_temp_task[i++]);
							pp_temp_core[3]->remove_one_task(0);
							if (temp_task_prio)
							{
								core_res_re += temp_task_com;
							}
							else
							{
								i--;
							}
						}
						for (z = 0; z < i; z++)
						{
							pp_temp_core[0]->add_one_task(*(pp_temp_task[z]), 0);
						}
					}
				}
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

int schedule::load_balance_to_two_core(multi_core* m_c)        //在面对只有两个处理器核心时，如果出现重载核，不管有几个，都将两个处理器核心上的任务均分
{
	int i, z;
	core** pp_temp_core;
	task*** q;
	task** pp_temp_task;
	task** p;
	int** task_num;
	int* temp_task_num;
	int* task_n;
	task*** qua_task;
	int* qua_task_num;
	task_n = new int;
	int temp_pp_task_num;
	int q_no;
	int temp_multi_core_res_re = 0;
	int temp_qua_task_com_res = 0;
	int temp_res_dif_v;
	q = new task * *[2];
	task_num = new int* [2];
	p = new task * [2048];
	int core_no[2] = { 0,1 };
	int have_height_core = 0;
	task** p_temp_task;
	qua_task = new task * *[2];
	qua_task_num = new int[2];
	for (i = 0; i < 2; i++)
	{
		p_temp_task = new task * [1024];
		qua_task[i] = p_temp_task;
		qua_task_num[i] = 0;
	}
	pp_temp_core = (*m_c).get_p_core();
	for (i = 0; i < 2; i++)
	{
		if (check_core_statu(*(pp_temp_core[i])))
		{
			have_height_core++;
		}
	}
	if (have_height_core)
	{
		for (z = 0; z < 2; z++)
		{
			temp_task_num = new int;
			task_num[z] = temp_task_num;
			pp_temp_task = new task * [1024];
			q[z] = pp_temp_task;
		}
		get_task_queue((*m_c), core_no, 2, q, task_num);
		get_task_pp(q, task_num, 2, p, task_n);
		sort_prio(p, *task_n);
		//DivQuadrants_2(qua_task, qua_task_num);
		temp_pp_task_num = (*task_n);
		while (*task_n > 0)
		{
			q_no = select_min_queue_2(qua_task[0], qua_task[1], qua_task_num[0], qua_task_num[1]);
			Insert_task(qua_task[q_no], &qua_task_num[q_no], p[temp_pp_task_num - (*task_n)]);
			(*task_n)--;
		}
		for (i = 0; i < 2; i++)
		{
			temp_multi_core_res_re = (pp_temp_core[i])->get_com_res_re();
			temp_qua_task_com_res = get_qua_task_com_res(qua_task[i], qua_task_num[i]);
			temp_res_dif_v = temp_qua_task_com_res - temp_multi_core_res_re;
			if (temp_res_dif_v > 0)
			{
				trimTask((*m_c), qua_task[i], &(qua_task_num[i]), i, qua_task, qua_task_num, temp_res_dif_v);
			}
		}
		for (i = 0; i < 2; i++)
		{
			(pp_temp_core[i])->add_task_p(qua_task[i], qua_task_num[i], i);
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

int schedule::DLBQ_load_balance_schedule(multi_core* m_c)
{
	int i, multi_core_num;
	int* core_no;
	int z, x, c;
	core_no = new int[1024];
	int h_core_num = 0;;
	core** pp_temp_core;
	task*** q;
	task** pp_temp_task;
	task*** qua_task;
	int* qua_task_num;
	task** p;
	multi_core** re_m_c;
	re_m_c = new multi_core* [4];
	p = new task * [1048576];
	int* task_n;
	task_n = new int;
	*task_n = 0;
	q = new task * *[1024];
	int** task_num;
	int* temp_task_num;
	task_num = new int* [1024];
	int q_no;
	int temp_pp_task_num;
	int temp_multi_core_res_re = 0;
	int temp_qua_task_com_res = 0;
	int temp_res_dif_v;
	int have_height_core = 0;
	task** p_temp_task;
	qua_task = new task * *[4];
	qua_task_num = new int[4];
	for (i = 0; i < 4; i++)
	{
		p_temp_task = new task * [1024];
		qua_task[i] = p_temp_task;
		qua_task_num[i] = 0;
	}
	multi_core_num = (*m_c).get_core_num();
	if (multi_core_num == 8)
	{
		load_balance_to_eight_core(m_c);
		return 0;
	}
	else if (multi_core_num == 2)
	{
		load_balance_to_two_core(m_c);
		return 0;
	}
	else if(multi_core_num == 1)
	{
		return 0;
	}
	pp_temp_core = (*m_c).get_p_core();
	for (i = 0; i < multi_core_num; i++)
	{
		if (check_core_statu(*(pp_temp_core[i])))
		{
			core_no[h_core_num++] = i;
			have_height_core++;
		}
	}
	if (have_height_core)
	{
		for (z = 0; z < 1024; z++)
		{
			temp_task_num = new int;
			task_num[z] = temp_task_num;
			pp_temp_task = new task * [1024];
			q[z] = pp_temp_task;
		}
		get_task_queue((*m_c), core_no, h_core_num, q, task_num);
		get_task_pp(q, task_num, h_core_num, p, task_n);
		sort_prio(p, *task_n);
		get_cores((*m_c), re_m_c);
		//DivQuadrants(qua_task, qua_task_num);
		temp_pp_task_num = (*task_n);
		while (*task_n > 0)
		{
			q_no = select_min_queue(qua_task[0], qua_task[1], qua_task[2], qua_task[3], qua_task_num[0], qua_task_num[1], qua_task_num[2], qua_task_num[3]);
			Insert_task(qua_task[q_no], &qua_task_num[q_no], p[temp_pp_task_num - (*task_n)]);
			(*task_n)--;
		}
		for (i = 0; i < 4; i++)
		{
			temp_multi_core_res_re = (re_m_c[i])->get_multi_core_res_re();
			temp_qua_task_com_res = get_qua_task_com_res(qua_task[i], qua_task_num[i]);
			temp_res_dif_v = temp_qua_task_com_res - temp_multi_core_res_re;
			if (temp_res_dif_v > 0)
			{
				trimTask((*m_c), qua_task[i], &(qua_task_num[i]), i, qua_task, qua_task_num, temp_res_dif_v);
			}
		}
		for (i = 0; i < 4; i++)
		{
			migrateTask(qua_task[i], qua_task_num[i], re_m_c, (*m_c), i);
		}
		for (i = 0; i < 4; i++)
		{
			DLBQ_load_balance_schedule(re_m_c[i]);

		}
	}
	else
	{
		return  0;
	}
	return 0;
}

int schedule::Base_load_balance_schedule(multi_core* m_c)
{
	int i, multi_core_num;
	int* core_no;
	int z, x, c;
	core_no = new int[1024];
	int h_core_num = 0;;
	core** pp_temp_core;
	task*** q;
	task** pp_temp_task;
	task*** qua_task;
	int* qua_task_num;
	task** p;
	multi_core** re_m_c;
	re_m_c = new multi_core * [4];
	p = new task * [1048576];
	int* task_n;
	task_n = new int;
	q = new task * *[1024];
	int** task_num;
	int* temp_task_num;
	task_num = new int* [1024];
	int q_no;
	int temp_pp_task_num;
	int temp_multi_core_res_re = 0;
	int temp_qua_task_com_res = 0;
	int temp_res_dif_v;
	int have_height_core = 0;
	task** p_temp_task;
	qua_task = new task * *[4];
	qua_task_num = new int[4];
	for (i = 0; i < 4; i++)
	{
		p_temp_task = new task * [1024];
		qua_task[i] = p_temp_task;
		qua_task_num[i] = 0;
	}
	multi_core_num = (*m_c).get_core_num();
	if (multi_core_num == 8)
	{
		load_balance_to_eight_core(m_c);
		return 0;
	}
	else if (multi_core_num == 2)
	{
		load_balance_to_two_core(m_c);
		return 0;
	}
	else if (multi_core_num == 1)
	{
		return 0;
	}
	pp_temp_core = (*m_c).get_p_core();
	for (i = 0; i < multi_core_num; i++)
	{
		if (check_core_statu(*(pp_temp_core[i])))
		{
			core_no[h_core_num++] = i;
			have_height_core++;
		}
	}
	if (have_height_core)
	{
		for (z = 0; z < 1024; z++)
		{
			temp_task_num = new int;
			task_num[z] = temp_task_num;
			pp_temp_task = new task * [1024];
			q[z] = pp_temp_task;
		}
		get_task_queue((*m_c), core_no, h_core_num, q, task_num);
		get_task_pp(q, task_num, h_core_num, p, task_n);
		sort_prio(p, *task_n);
		get_cores((*m_c), re_m_c);
		//DivQuadrants(qua_task, qua_task_num);
		temp_pp_task_num = (*task_n);
		while (*task_n > 0)
		{
			q_no = select_min_task_num_queue(qua_task_num[0], qua_task_num[1], qua_task_num[2], qua_task_num[3]);
			Insert_task(qua_task[q_no], &qua_task_num[q_no], p[temp_pp_task_num - (*task_n)]);
			(*task_n)--;
		}
		for (i = 0; i < 4; i++)
		{
			temp_multi_core_res_re = (re_m_c[i])->get_multi_core_res_re();
			temp_qua_task_com_res = get_qua_task_com_res(qua_task[i], qua_task_num[i]);
			temp_res_dif_v = temp_qua_task_com_res - temp_multi_core_res_re;
			if (temp_res_dif_v > 0)
			{
				trimTask((*m_c), qua_task[i], &(qua_task_num[i]), i, qua_task, qua_task_num, temp_res_dif_v);
			}
		}
		for (i = 0; i < 4; i++)
		{
			migrateTask_B(qua_task[i], qua_task_num[i], re_m_c, (*m_c), i);
		}
		for (i = 0; i < 4; i++)
		{
			Base_load_balance_schedule(re_m_c[i]);
		}
	}
	else
	{
		return  0;
	}
	return 0;
}