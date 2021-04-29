
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

class math
{
private:
	double result;
public:
	math();
	double get_result();
	int S_D_double_sq(double* p, int n);      //返回标准差的平方
	double S_D_double_sq_new_1(double** p, int n, int m);
	int int_min(int* p, int n);               //返回数组中最小值的位置
	int get_2_order(int num);
	int get_i_for_DLBQ(int num);
	int get_j_for_DLBQ(int num);
	int get_q_for_DLBQ(int num, int* re_num);
	int get_empty_core_location(int* num, int core_j, int* re_num, int core_i);
	int get_line_on_even_k(int core_num, int i, int j);
	int get_column_on_even_k(int core_num, int i, int j);
	int get_line_on_odd_k(int core_num, int i, int j);
	int get_column_on_odd_k(int core_num, int i, int j);
	int get_random(int n);
};
