#pragma once
#include "thread.h"


class process
{
private:
	int pro_ID;              //process number
	int thread_num;           // process's thread number
public:
	process();
	process(int id, int th_num);
};