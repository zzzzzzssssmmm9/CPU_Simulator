#include "main.h"
using namespace std;

int main()
{
	sys s;
	int* height_core_no;
	int height_core_num = 2;
	int i;
	height_core_no = new int[height_core_num];
	for (i = 0; i < height_core_num; i++)
	{
		height_core_no[i] = i * 3;
	}
	s.run(16, height_core_num, height_core_no, 1.0, 100, 30, 20);
	return 0;
}