#include "random.h"

random::random()
{
	seed = 10;
}

random::random(int s)
{
	seed = s;
}

int random::set_seed()
{
	int modle;
	printf("input what modle you want: ( 0 ) default random seed / ( 1 ) input random seed / ( 2 ) time as random seed\n");
	scanf("%d", &modle);
	switch (modle)
	{
	case 0:
		break;
	case 1:
		printf("input time seed\n");
		scanf("%d", &seed);
		break;
	case 2:
		seed = (int)time(NULL);
		break;
	default:
		printf("you input is error!\n");
		return 1;
	}
	srand(seed);
	return 0;
}

int random::get_random()
{
	return rand();
}