#include "thread.h"

thread::thread()
{
	thread_ID = 0;
}

thread::thread(int id)
{
	thread_ID = id;
}