#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

class random
{
private:
	int seed;
public:
	random();
	random(int s);
	int set_seed();
	int get_random();
};