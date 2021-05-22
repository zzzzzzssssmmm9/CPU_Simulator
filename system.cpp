#include "system.h"

sys::sys()
{
	sche.set_modle(1);
}

int sys::run()
{
	int* height_core_no;
	int height_core_num = 2;
	int i;
	double time = 0;
	int count = 0;
	height_core_no = new int[height_core_num];
	for (i = 0; i < height_core_num; i++)
	{
		height_core_no[i] = i * 3;
	}
	height_core_no[0] = 0;
	height_core_no[1] = 2;
	//height_core_no[2] = 6;
	//height_core_no[3] = 12;
	core_init(16, height_core_num, height_core_no, 1.0, 100, 30, 100, 1, 900);
	while (1)
	{
		if (count % 10 == 0)
		{
			cout << "system rum time now: " << time << "s" << endl;
			core_run(1);
		}
		if (count % 4 == 0)
		{
			load_balance(16); //core num; height core num; height core no; height core threshold; task time; task com; task num grad
		}
		if (count % 2 == 1)
		{
			core_add_task(1, 100, 30);
		}
		time += 0.1;
		count++;
	}
	return 0;
}

int sys::load_balance(int core_num)
{
	int i;
	core** p;
	cout << "m_c_1" << endl;
 	sche.DLBQ_load_balance_schedule(&m_c_1);
	cout << "m_c_2" << endl;
	sche.Base_load_balance_schedule(&m_c_2);
	p = m_c_1.get_p_core();
	cout << "m_c_1:" << endl;
	for (i = 0; i < core_num; i++)
	{
		cout << "core no: " << i << " core comput: " << p[i]->get_comput() << " core com res re: " << p[i]->get_com_res_re() << " core state: " << p[i]->get_state() << " core task num: " << p[i]->get_task_num() << " core com res use: " << p[i]->get_com_res_use() << endl;
	}
	p = m_c_2.get_p_core();
	cout << "m_c_2:" << endl;
	for (i = 0; i < core_num; i++)
	{
		cout << "core no: " << i << " core comput: " << p[i]->get_comput() << " core com res re: " << p[i]->get_com_res_re() << " core state: " << p[i]->get_state() << " core task num: " << p[i]->get_task_num() << " core com res use: " << p[i]->get_com_res_use() << endl;
	}
	get_LBD();
	compare_multi_core_run_time();
 	return 0;
}

int sys::core_run(int time)
{
	m_c_1.multi_core_run(time);
	m_c_2.multi_core_run(time);
	return 0;
}

int sys::core_add_task(int task_num, int task_run_time, int task_com)
{
	task** pp_temp_task_1;
	task** pp_temp_task_2;
	task** pp_temp_task_3;
	task* temp_task;
	int i;
	int core_num;
	int temp_core_no_1 = m_c_1.get_alloc_task_core_no();
	int temp_core_no_2 = m_c_2.get_alloc_task_core_no();
	int temp_core_no_3 = m_c_3.get_alloc_task_core_no();
	pp_temp_task_1 = new task * [task_num];
	pp_temp_task_2 = new task * [task_num];
	pp_temp_task_3 = new task * [task_num];
	core** p_c_1, ** p_c_2, ** p_c_3;
	core_num = m_c_1.get_core_num();
	p_c_1 = m_c_1.get_p_core();
	p_c_2 = m_c_2.get_p_core();
	p_c_3 = m_c_3.get_p_core();
	create_task(task_num, task_run_time, task_com, pp_temp_task_1);
	for (i = 0; i < task_num; i++)
	{
		temp_task = new task;
		*temp_task = *pp_temp_task_1[i];
		pp_temp_task_2[i] = temp_task;
		temp_task = new task;
		*temp_task = *pp_temp_task_1[i];
		pp_temp_task_3[i] = temp_task;
	}
	for (i = 0; i < task_num; i++)
	{
		p_c_1[temp_core_no_1]->add_one_task(*pp_temp_task_1[i], temp_core_no_1);
		p_c_2[temp_core_no_2]->add_one_task(*pp_temp_task_2[i], temp_core_no_2);
		p_c_3[temp_core_no_3]->add_one_task(*pp_temp_task_3[i], temp_core_no_3);
		temp_core_no_1 = (temp_core_no_1 + 1) % core_num;
		temp_core_no_2 = (temp_core_no_2 + 1) % core_num;
		temp_core_no_3 = (temp_core_no_3 + 1) % core_num;
	}
	m_c_1.set_alloc_task_core_no(temp_core_no_1);
	m_c_2.set_alloc_task_core_no(temp_core_no_2);
	m_c_3.set_alloc_task_core_no(temp_core_no_3);
	return 0;
}

int sys::core_init(int core_num, int height_num, int* height_core_no, double height_state, int task_run_time, int task_com, int task_grad, int task_num_modle, int t_n)
{
	math m;
	int i, z, task_num = 0, task_all_com, core_com;
	cout << "Fuck You" << endl;
	task** pp_t_1, ** pp_t_2, ** pp_t_3;
	task* temp_task;
	core** p;
	//int* height_core_no;
	//height_core_no = new int[height_num];
	pp_t_1 = new task * [1000];
	pp_t_2 = new task * [1000];
	pp_t_3 = new task * [1000];
	while (!task_num)
	{
		task_num = m.get_random(10) * task_grad;
	}
	if (task_num_modle)
	{
		task_num = t_n;
	}
	cout << "task num:" << task_num << endl;
	create_task(task_num, task_run_time, task_com, pp_t_1);
	for (i = 0; i < task_num; i++)
	{
		temp_task = new task;
		*temp_task = *pp_t_1[i];
		pp_t_2[i] = temp_task;
		temp_task = new task;
		*temp_task = *pp_t_1[i];
		pp_t_3[i] = temp_task;
	}
	/**/
	for (i = 0; i < task_num; i++)
	{
		cout << "task time:" << pp_t_1[i]->get_time() << " task com " << pp_t_1[i]->get_com() << " task prio " << pp_t_1[i]->get_prio() << " task id " << pp_t_1[i]->get_ID() << endl;
	}
	/**/
	task_all_com = get_all_task_com(pp_t_1, task_num);
	core_com = (task_all_com / core_num) * 0.9;// *1.2;// *0.9;// *2// * 1;
	create_multi_core(core_num, core_com, height_state);
	/*
	for (i = 0; i < height_num; i++)
	{
		height_core_no[i] = i * 3;
	}
	*/
	if (allo_task_to_core(pp_t_1, pp_t_2, pp_t_3, task_num, height_core_no, height_num, core_com))
	{
		cout << "allo_task error!" << endl;
		return 0;
	}
	p = m_c_1.get_p_core();
	cout << "m_c_1:" << endl;
	for (i = 0; i < core_num; i++)
	{
		cout << "core no: " << i << " core comput: " << p[i]->get_comput() << " core com res re: " << p[i]->get_com_res_re() << " core state: " << p[i]->get_state() << " core task num: " << p[i]->get_task_num() << " core com res use: " << p[i]->get_com_res_use() << endl;
	}
	p = m_c_2.get_p_core();
	cout << "m_c_2:" << endl;
	for (i = 0; i < core_num; i++)
	{
		cout << "core no: " << i << " core comput: " << p[i]->get_comput() << " core com res re: " << p[i]->get_com_res_re() << " core state: " << p[i]->get_state() << " core task num: " << p[i]->get_task_num() << " core com res use: " << p[i]->get_com_res_use() << endl;
	}
	return 0;
}

int sys::create_multi_core(int core_num, int com, double height_state)
{
	core** p_1, ** p_2, ** p_3;
	core* temp_p;
	int i;
	p_1 = new core * [core_num];
	p_2 = new core * [core_num];
	p_3 = new core * [core_num];
	for (i = 0; i < core_num; i++)
	{
		temp_p = new core;
		temp_p->set_comput(com);
		temp_p->set_state_ratio(0.2, 0.5, height_state);
		p_1[i] = temp_p;
		temp_p = new core;
		temp_p->set_comput(com);
		temp_p->set_state_ratio(0.2, 0.5, height_state);
		p_2[i] = temp_p;
		temp_p = new core;
		temp_p->set_comput(com);
		temp_p->set_state_ratio(0.2, 0.5, height_state);
		p_3[i] = temp_p;
	}
	m_c_1.set_core(core_num, p_1);
	m_c_2.set_core(core_num, p_2);
	m_c_3.set_core(core_num, p_3);
	return 0;
}

int sys::allo_task_to_core(task** p_1, task** p_2, task** p_3, int task_num, int* height_core_no, int height_core_num, int core_com)
{
	int core_num, i, com = 0, task_no = 0;
	core** p_c_1,**p_c_2,**p_c_3;
	core_num = m_c_1.get_core_num();
	p_c_1 = m_c_1.get_p_core();
	p_c_2 = m_c_2.get_p_core();
	p_c_3 = m_c_3.get_p_core();
	for (i = 0; i < height_core_num; i++)
	{
		com = 0;
		while (com <= core_com)
		{
			p_c_1[height_core_no[i]]->add_one_task(*p_1[task_no], height_core_no[i]);
			p_c_2[height_core_no[i]]->add_one_task(*p_2[task_no], height_core_no[i]);
			p_c_3[height_core_no[i]]->add_one_task(*p_3[task_no], height_core_no[i]);
			if (p_1[task_no]->get_prio() != 0)
			{
				com += p_1[task_no]->get_com();
			}
			task_no++;
		}
	}
	i = 0;
	while (task_no < task_num)
	{
		if (check_is_height_core(height_core_no, height_core_num, (i%core_num)))
		{

		}
		else
		{
			if (p_c_1[(i % core_num)]->get_com_res_re() > 30)
			{
				p_c_1[(i % core_num)]->add_one_task(*p_1[task_no], (i % core_num));
				p_c_2[(i % core_num)]->add_one_task(*p_2[task_no], (i % core_num));
				p_c_3[(i % core_num)]->add_one_task(*p_3[task_no], (i % core_num));
				task_no++;
			}
		}
		i++;
	}
	m_c_1.set_alloc_task_core_no(i % core_num);
	m_c_2.set_alloc_task_core_no(i % core_num);
	m_c_3.set_alloc_task_core_no(i % core_num);
	return 0;
}

int sys::check_is_height_core(int* height_core_no, int height_core_num, int no)
{
	int i;
	for (i = 0; i < height_core_num; i++)
	{
		if (height_core_no[i] == no)
		{
			return 1;
		}
	}
	return 0;
}

int sys::create_task(int num, int run_time, int com, task** p)
{
	math m;
	int i;
	for (i = 0; i < num; i++)
	{
		p[i] = new task;
		create_one_task(p[i], m.get_random(run_time), m.get_random(com), m.get_random(5), i);
		Sleep(100);
	}
	return 0;
}

int sys::create_one_task(task* p, int run_time, int com, int prio, int task_no)
{
	p->set_run_time(run_time);
	p->set_com(com);
	p->set_prio(prio);
	p->set_id(task_no);
	return 0;
}

int sys::get_all_task_com(task** p, int task_num)
{
	int task_com = 0;
	int i;
	for (i = 0; i < task_num; i++)
	{
		task_com += p[i]->get_com();
	}
	return task_com;
}

int sys::get_one_core_all_task_run_time(core* c, double* re_time)
{
	task** pp_temp_task;
	int* re_task_num;
	int i;
	int temp_task_prio;
	re_task_num = new int;
	*re_task_num = 0;
	pp_temp_task = new task * [1000];
	c->get_all_task(pp_temp_task, re_task_num);
	*re_time = 0;
	for (i = 0; i < *re_task_num; i++)
	{
		temp_task_prio = pp_temp_task[i]->get_prio();
		if (temp_task_prio)
		{
			if (temp_task_prio == 1)
			{
				(*re_time) += (pp_temp_task[i]->get_time()*0.5);
			}
			else
			{
				(*re_time) += pp_temp_task[i]->get_time();
			}
		}
	}
	return 0;
}

int sys::compare_multi_core_run_time()
{
	core** pp_temp_core;
	int temp_core_num;
	int i;
	double* temp_max_time;
	double max_time;
	temp_max_time = new double;
	pp_temp_core = m_c_1.get_p_core();
	temp_core_num = m_c_1.get_core_num();
	max_time = 0;
	for (i = 0; i < temp_core_num; i++)
	{
		get_one_core_all_task_run_time(pp_temp_core[i], temp_max_time);
		if (max_time < *temp_max_time)
		{
			max_time = *temp_max_time;
		}
	}
	cout << "m_c_1 max run time: " << max_time << endl;

	pp_temp_core = m_c_2.get_p_core();
	temp_core_num = m_c_2.get_core_num();
	max_time = 0;
	for (i = 0; i < temp_core_num; i++)
	{
		get_one_core_all_task_run_time(pp_temp_core[i], temp_max_time);
		if (max_time < *temp_max_time)
		{
			max_time = *temp_max_time;
		}
	}
	cout << "m_c_2 max run time: " << max_time << endl;
	return 0;
}

int sys::get_LBD()
{
	math m;
	int** temp_num;
	int* temp_core_num;
	int** temp_core_have_task_num;
	int* temp_n;
	int i;
	int z;
	core** pp_temp_core;
	task** pp_temp_task;
	int* re_task_num;
	int load_balance_class;
	pp_temp_task = new task * [1000];
	re_task_num = new int;
	temp_num = new int* [1000];
	temp_core_num = new int;
	*temp_core_num = m_c_1.get_core_num();
	temp_core_have_task_num = new int* [*temp_core_num];
	pp_temp_core = m_c_1.get_p_core();
	for (i = 0; i < *temp_core_num; i++)
	{
		temp_core_have_task_num[i] = new int;
		temp_n = new int[1000];
		temp_num[i] = temp_n;
	}
	//m_c_1.get_core_task_num(0, *temp_core_num, temp_core_have_task_num);
	cout << "m_c_1 task: " << endl;
	for (i = 0; i < *temp_core_num; i++)
	{
		pp_temp_core[i]->get_all_task(pp_temp_task, re_task_num);
		*temp_core_have_task_num[i] = *re_task_num;
		for (z = 0; z < *re_task_num; z++)
		{
			temp_num[i][z] = pp_temp_task[z]->get_time();
			cout << temp_num[i][z] << " ";
		}
		cout << endl;
	}
	load_balance_class = m.S_D_int_sq(temp_num, temp_core_num, temp_core_have_task_num);
	free(temp_core_have_task_num);
	cout << "m_c_1 load balance class: " << load_balance_class << endl;

	*temp_core_num = m_c_2.get_core_num();
	temp_core_have_task_num = new int* [*temp_core_num];
	pp_temp_core = m_c_2.get_p_core();
	for (i = 0; i < *temp_core_num; i++)
	{
		temp_core_have_task_num[i] = new int;
		temp_n = new int[1000];
		temp_num[i] = temp_n;
	}
	//m_c_2.get_core_task_num(0, *temp_core_num, temp_core_have_task_num);
	cout << "m_c_2 task: " << endl;
	for (i = 0; i < *temp_core_num; i++)
	{
		pp_temp_core[i]->get_all_task(pp_temp_task, re_task_num);
		*temp_core_have_task_num[i] = *re_task_num;
		for (z = 0; z < *re_task_num; z++)
		{
			temp_num[i][z] = pp_temp_task[z]->get_time();
			cout << temp_num[i][z] << " ";
		}
		cout << endl;
	}
	load_balance_class = m.S_D_int_sq(temp_num, temp_core_num, temp_core_have_task_num);
	free(temp_core_have_task_num);
	cout << "m_c_2 load balance class: " << load_balance_class << endl;
	return 0;
}
