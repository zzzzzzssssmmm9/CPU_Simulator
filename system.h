#pragma once
#include "scheduler.h"
#include <iostream>
using namespace std;

class sys
{
private:
	schedule sche;
	multi_core m_c;
	core c;
public:
	sys();
	int run();
};