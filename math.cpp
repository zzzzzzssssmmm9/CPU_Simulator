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

int math::int_min(int* p, int n)
{
	int i, p_min = 0, min = p[p_min];
	for (i = 1; i < n; i++)
	{
		if (min > p[i])
		{
			p_min = i;
			min = p[p_min];
		}
	}
	return p_min;
}

int math::get_2_order(int num)
{
	int result=0;
	int i, z = 1;
	if (num == 1)
	{
		return 0;
	}
	for (i = 2;; i*2, z++)
	{
		if (num == i)
		{
			result = z;
			break;
		}
	}
	return result;
}

int math::get_i_for_DLBQ(int num)
{
	int i,result=1;
	if (num <= 3)
	{
		return num;
	}
	if (num % 2 == 0)
	{
		for (i = 0; i < (num / 2); i++)
		{
			result *= 2;
		}
	}
	else
	{
		for (i = 0; i < ((num - 3) / 2); i++)
		{
			result *= 2;
		}
		result *= 3;
	}
	return result;
}

int math::get_j_for_DLBQ(int num)
{
	int i, result = 1;
	for (i = 0; i < ((num - 3) / 2); i++)
	{
		result *= 2;
	}
	return result;
}

int math::get_q_for_DLBQ(int num, int* re_num)
{
	int i,j;
	j = get_j_for_DLBQ(num);
	for (i = 1; i <= j; i++)
	{
		re_num[i - 1] = 3 * i - 1;
	}
	return 0;
}

int math::get_empty_core_location(int* num, int core_j, int* re_num, int core_i)
{
	int i,z,x=0;
	for (i = 0; i < core_j; i++)
	{
		for (z = 0; z < core_j; z++)
		{
			re_num[x] = (num[i] - 1) * core_i + num[z] - 1;
			x++;
		}
	}
	return 0;
}

int math::get_line_on_even_k(int core_num, int i, int j)
{
	int line = 0;
	while (core_num >= i)
	{
		line++;
		core_num -= i;
	}
	return line;
}

int math::get_column_on_even_k(int core_num, int i, int j)
{
	int column = 0;
	while (core_num >= i)
	{
		core_num -= i;
	}
	column = core_num;
	return column;
}

int math::get_line_on_odd_k(int core_num, int i, int j)
{
	int line = 0, temp_i=0;
	int num = j * 8;
	while (core_num >= num)
	{
		temp_i++;
		core_num -= num;
	}
	if (core_num < i)
	{
		line = temp_i * 3;
	}
	else if (core_num < 2 * i - j)
	{
		line = temp_i + 3 + 1;
	}
	else
	{
		line = temp_i * 3 + 2;
	}
	return line;
}

int math::get_column_on_odd_k(int core_num, int i, int j)
{
	int colum = 0;
	int num = j * 8;
	while (core_num >= num)
	{
		core_num -= num;
	}
	if (core_num < i)
	{
		colum = core_num;
	}
	else if (core_num < 2 * i - j)
	{
		core_num -= i;
		while (core_num >= 2)
		{
			colum += 3;
			core_num -= 2;
		}
		colum += core_num * 2;
	}
	else
	{
		colum = core_num - 2 * i + j;
	}
	return colum;
}