#include "math.h"

math::math()
{
	result = 0;
}

double math::get_result()
{
	return result;
}

int math::S_D_double_sq(double* p, int n)
{
	int i;
	double num1 = 0, num2 = 0;
	for (i = 0; i < n; i++)
	{
		num1 += p[i];
	}
	num1 /= n;
	for (i = 0; i < n; i++)
	{
		num2 += (p[i] - num1) * (p[i] - num1);
	}
	num2 /= n;
	result = num2;
	return 0;
}

double math::S_D_double_sq_new_1(double** p, int n, int m)
{
	int i,z;
	double num1 = 0, num2 = 0, num3 = 0;
	for (i = 0; i < n; i++)
	{
		for (z = 0; z < m; z++)
		{
			num1 += p[i][z];
		}
	}
	num1 /= n;
	for (i = 0; i < n; i++)
	{
		num2 = 0;
		for (z = 0; z < m; z++)
		{
			num2 += p[i][z];
		}
		num3 = (num2 - num1)* (num2 - num1);
	}
	num3 = num3 / n;
	return num3;
}