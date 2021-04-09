#include "initialize.h"

int init()
{
	int model;
	int ret = 1;
	cout << "input single core( 0 ) or multi core ( 1 )" << endl;
	cin >> model;
	cout << endl;
	if (model)
	{
		ret = init_multi();
	}
	else
	{
		ret = init_sigle();
	}
	return ret;
}

int init_single()
{
	
	return 0;
}

int init_multi()
{
	return 0;
}

int cpu()
{
	return 0;
}

int mem()
{
	return 0;
}

int IO()
{
	return 0;
}

int task()
{
	return 0;
}