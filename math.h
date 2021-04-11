
#pragma once
#include <stdlib.h>
#include <stdio.h>

class math
{
private:
	double result;
public:
	math();
	double get_result();
	int S_D_double_sq(double* p, int n);      //返回标准差的平方
	double S_D_double_sq_new_1(double** p, int n, int m);
};
