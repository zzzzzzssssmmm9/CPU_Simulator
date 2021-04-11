#include "cpu.h"

int i;
core* p_temp_core;
task* p_temp_task;

core::core()
{
	computing_resource = 10;
	state = 0;
	comput_res_re = 10;
	comput_res_use = 0;
	L_state = 0.2;
	M_state = 0.5;
	H_state = 0.8;
	p_task_start = new ttask;
	p_task_end = p_task_start;
	p_task_start->p = NULL;
	task_num = 0;
	task_num_limit = 1024;
}

core::core(int num, double L, double M, double H)
{
	computing_resource = num;
	state = 0;
	comput_res_re = num;
	comput_res_use = 0;
	L_state = L;
	M_state = M;
	H_state = H;
	p_task_start = new ttask;
	p_task_end = p_task_start;
	p_task_start->p = NULL;
	task_num = 0;
	task_num_limit = 1024;
}

int core::set_core()
{
	ttask* p;
	int i;
	printf("input computing resource, comput resource residue, comput resource use, low load state, medium load state, high load state, task num, task num limit\n");
	scanf("%d,%d,%d,%f,%f,%f,%d,%d", &computing_resource, &comput_res_re, &comput_res_use, &L_state, &M_state, &H_state, &task_num, &task_num_limit);
	for (i = 0; i < task_num; i++)
	{
		p = new ttask;
		p->p = NULL;
		p_task_end->p = p;
		p_task_end = p_task_end->p;
	}
	return 0;
}

int core::release_one_res()
{
	if (comput_res_use > 0)
	{
		comput_res_re++;
		comput_res_use--;
		check_state();
		return 0;
	}
	else
	{
		return 1;
	}
}

int core::use_one_res()
{
	//if (comput_res_re > 0)
	//{
		comput_res_re--;
		comput_res_use++;
		check_state();
		return 0;
	//}
	//else
	//{
	//	return 1;
	//}
}

int core::release_res(int n)    //返回剩余几个分配失败
{
	for (; n > 0 && comput_res_use > 0; n--)
		release_one_res();
	return n;
}

int core::use_res(int n)
{
	for (; n > 0; n--)   //for (; n > 0 && comput_res_re > 0; n--)
		use_one_res();
	return n;
}

int core::check_state()
{
	if (comput_res_use > H_state * computing_resource)
	{
		state = 3;
	}
	else if (comput_res_use > M_state * computing_resource)
	{
		state = 2;
	}
	else if (comput_res_use > L_state * computing_resource)
	{
		state = 1;
	}
	else
	{
		state = 0;
	}
	return 0;
}

int core::set_state_ratio(double L, double M, double H)
{
	L_state = L;
	M_state = M;
	H_state = H;
	return 0;
}

int core::set_state()
{
	double L, M, H;
	printf("input Low ratio, Mediun ratio, Hight ratio\n");
	scanf("%f,%f,%f", &L, &M, &H);
	set_state_ratio(L, M, H);
	return 0;
}

int core::add_one_task(task t)
{
	ttask* p;
	if (task_num < task_num_limit)
	{
		p = new ttask;
		p->T = t;
		p->p = NULL;
		p_task_end->p = p;
		p_task_end = p_task_end->p;
		use_res(t.get_com());
		return 0;
	}
	else
	{
		return 1;
	}
}

int core::add_task(task* p, int n)       //返回有几个任务分配失败
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (add_one_task(p[i]))
		{
			return n - i;
		}
	}
	return 0;
}

int core::remove_one_task()
{
	ttask* p;
	if (task_num > 0)
	{
		p = p_task_start->p;
		if (release_res(p->T.get_com()))
		{
			printf("CPU remove task error ( use resoure not enough\n )");
			return 1;
		}
		else
		{
			p_task_start->p = p->p;
			free(p);
		}
	}
	return 0;
}

int core::remove_task(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (remove_one_task())
			return 1;
	}
	return 0;
}

ttask* core::get_p_task_start()
{
	return p_task_start;
}

ttask* core::get_p_task_end()
{
	return p_task_end;
}

multi_core::multi_core()
{
	core_num = 10;
	state = 0;
	p_core = new core * [1024];
	for (i = 0; i < 10; i++)
	{
		p_temp_core = new core;
		p_core[i] = p_temp_core;
	}
}

multi_core::multi_core(int num, double L, double M, double H)
{
	core_num = num;
	state = 0;
	p_core = new core * [1024];
	for (i = 0; i < num; i++)
	{
		p_temp_core = new core;
		p_core[i] = p_temp_core;
	}
	set_multi_core_state_ratio(L, M, H);
}

int multi_core::set_multi_core_state_ratio(double L, double M, double H)
{
	for (i = 0; i < core_num; i++)
	{
		p_core[i]->set_state_ratio(L, M, H);
	}
	return 0;
}

int multi_core::set_multi_core()
{
	double L, M, H;
	printf("input core number, state ratio\n");
	scanf("%d,%f,%f,%f", &core_num, &L, &M, &H);
	state = 0;
	for (i = 0; i < core_num; i++)
	{
		p_temp_core = new core;
		p_core[i] = p_temp_core;
	}
	set_multi_core_state_ratio(L, M, H);
	return 0;
}

int multi_core::release_one_core_res(int no, int num)
{
	p_temp_core = p_core[no];
	if (p_temp_core->release_res(num))
	{
		return 1;
	}
	return 0;
}

int multi_core::use_one_core_res(int no, int num)
{
	p_temp_core = p_core[no];
	p_temp_core->use_res(num);
	return 0;
}

int multi_core::release_res()
{
	return 0;
}

int multi_core::use_res()
{
	return 0;
}

int multi_core::check_state()
{
	return 0;
}

int multi_core::add_one_core_task(int no, task* p, int n)   //返回有几个任务分配失败
{
	p_temp_core = p_core[no];
	return p_temp_core->add_task(p, n);
}

int multi_core::add_task()
{
	return 0;
}

int multi_core::remove_one_core_task(int no, int n)
{
	p_temp_core = p_core[no];
	return p_temp_core->release_res(n);
}

int multi_core::remove_core_task()
{
	return 0;
}

int multi_core::get_core_num()
{
	return core_num;
}

ttask* multi_core::get_one_core_p_task_start(int no)
{
	p_temp_core = p_core[no];
	return p_temp_core->get_p_task_start();
}

ttask* multi_core::get_one_core_p_task_end(int no)
{
	p_temp_core = p_core[no];
	return p_temp_core->get_p_task_end();
}

ttask** multi_core::get_p_task_start()
{
	int i;
	ttask** p_temp_p_ttask;
	ttask* p_temp_ttask;
	p_temp_p_ttask = new ttask * [1024];
	for (i = 0; i < 1024; i++)
	{
		p_temp_ttask = p_core[i]->get_p_task_start();
		p_temp_p_ttask[i] = p_temp_ttask;
	}
	return p_temp_p_ttask;
}

ttask** multi_core::get_p_task_end()
{
	int i;
	ttask** p_temp_p_ttask;
	ttask* p_temp_ttask;
	p_temp_p_ttask = new ttask * [1024];
	for (i = 0; i < 1024; i++)
	{
		p_temp_ttask = p_core[i]->get_p_task_end();
		p_temp_p_ttask[i] = p_temp_ttask;
	}
	return p_temp_p_ttask;
}