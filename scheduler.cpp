#include "scheduler.h"


schedul::schedul()
{

}

double schedul::get_banlance_class(double** p, int n, int m)
{
	math m_f;
	return m_f.S_D_double_sq_new_1(p, n, m);
}

int schedul::add_one_task_to_one_core(core c, task* t)
{
	if (c.add_one_task(*t))
	{
		return 1;
	}
	return 0;
}

int schedul::add_task_to_one_core(core c, task* p, int n)
{
	if (c.add_task(p, n))
	{
		return 1;
	}
	return 0;
}

int schedul::add_task_to_core(multi_core m_c, int start_core_no, task** p, int core_num, int* n)
{
	m_c.add_task(start_core_no, p, core_num, n);
	return 0;
}

int schedul::get_one_core_task(core c, int start_no, int num, task** q)
{
	if (c.get_task(start_no, num, q))
	{
		return 1;
	}
	return 0;
}

int schedul::get_core_task()
{
	
	return 0;
}