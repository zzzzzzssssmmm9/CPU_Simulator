#include "main.h"
using namespace std;

int main()
{
	sys s;
	int* height_core_no;
	int height_core_num = 4;
	int i;
	height_core_no = new int[height_core_num];
	for (i = 0; i < height_core_num; i++)
	{
		height_core_no[i] = i * 3;
	}
	height_core_no[0] = 0;
	height_core_no[1] = 1;
	height_core_no[2] = 6;
	height_core_no[3] = 12;
	s.run(32, height_core_num, height_core_no, 1.0, 100, 30, 100, 1, 150); //core num; height core num; height core no; height core threshold; task time; task com; task num grad
	return 0;
}