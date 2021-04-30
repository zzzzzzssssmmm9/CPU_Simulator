#include "system.h"

sys::sys()
{
	sche.set_modle(1);
}

int sys::run(int core_num, int height_num, double height_state, int task_run_time, int task_com, int task_grad)
{
	math m;
	multi_core m_c_2;
	int i, z, task_num = 0, task_all_com, core_com;
	cout << "Fuck You" << endl;
	task** pp_t;
	core** p;
	int* height_core_no;
	height_core_no = new int[height_num];
	pp_t = new task * [1000];
	while (!task_num)
	{
		task_num = m.get_random(10) * task_grad;
	}
	create_task(task_num, task_run_time, task_com, pp_t);
	/**/
	for (i = 0; i < task_num; i++)
	{
		cout << "task time:" << pp_t[i]->get_time() << " task com " << pp_t[i]->get_com() << " task prio " << pp_t[i]->get_prio() << " task id " << pp_t[i]->get_ID() << endl;
	}
	/**/
	task_all_com = get_all_task_com(pp_t, task_num);
	core_com = (task_all_com / core_num) * 2;
	create_multi_core(core_num, core_com, height_state);
	for (i = 0; i < height_num; i++)
	{
		height_core_no[i] = i * 3;
	}
	allo_task_to_core(pp_t, task_num, height_core_no, height_num, core_com);
	m_c_2 = m_c;
	p = m_c.get_p_core();
	for (i = 0; i < core_num; i++)
	{
		cout << "core no: " << i << " core comput: " << p[i]->get_comput() << " core com res re: " << p[i]->get_com_res_re() << " core state: " << p[i]->get_state() << " core task num: " << p[i]->get_task_num() << " core com res use: " << p[i]->get_com_res_use() << endl;
	}
 	sche.DLBQ_load_balance_schedule(&m_c);
	p = m_c.get_p_core();
	for (i = 0; i < core_num; i++)
	{
		cout << "core no: " << i << " core comput: " << p[i]->get_comput() << " core com res re: " << p[i]->get_com_res_re() << " core state: " << p[i]->get_state() << " core task num: " << p[i]->get_task_num() << " core com res use: " << p[i]->get_com_res_use() << endl;
	}
	return 0;
}

int sys::create_multi_core(int core_num, int com, double height_state)
{
	core** p;
	core* temp_p;
	int i;
	p = new core * [core_num];
	for (i = 0; i < core_num; i++)
	{
		temp_p = new core;
		temp_p->set_comput(com);
		temp_p->set_state_ratio(0.2, 0.5, height_state);
		p[i] = temp_p;
	}
	m_c.set_core(core_num, p);
	return 0;
}

int sys::allo_task_to_core(task** p, int task_num, int* height_core_no, int height_core_num, int core_com)
{
	int core_num, i, com = 0, task_no = 0;
	core** p_c;
	core_num = m_c.get_core_num();
	p_c = m_c.get_p_core();
	for (i = 0; i < height_core_num; i++)
	{
		com = 0;
		while (com <= core_com)
		{
			p_c[height_core_no[i]]->add_one_task(*p[task_no], height_core_no[i]);
			if (p[task_no]->get_prio() != 0)
			{
				com += p[task_no]->get_com();
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
			p_c[(i % core_num)]->add_one_task(*p[task_no], (i % core_num));
			task_no++;
		}
		i++;
	}
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
